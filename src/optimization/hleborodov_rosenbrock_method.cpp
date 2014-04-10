#include <k52/optimization/hleborodov_rosenbrock_method.h>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <k52/optimization/params/i_continuous_parameters.h>

using ::std::vector;

namespace k52
{
namespace optimization
{

HleborodovRosenbrockMethod::HleborodovRosenbrockMethod(
    double precision = 1e-10,
    size_t max_iteration_number = 10000,
    double first_step = 1,
    double max_step = 3)
{
    precision_ = precision;

    arguments_increase_ = 1.5;
    arguments_decrease_ = -0.5;

    first_step_ = first_step;
    max_step_ = max_step;
    max_iteration_number_ = max_iteration_number;
}

void HleborodovRosenbrockMethod::Optimize(
    const IObjectiveFunction &function_to_optimize,
    IParameters* parametrs_to_optimize,
    bool maximize)
{
    IContinuousParameters* continuous_parameters = dynamic_cast<IContinuousParameters*> (parametrs_to_optimize);

    vector<double> arguments(continuous_parameters->GetValues());
    dimension_ = arguments.size();
    vector<double> next_step_arguments(arguments);

    InitializeBasisAndSteps();

    for(size_t i = 1; i<=max_iteration_number_; i++)
    {
        // Research of next arguments, that minimize function
        MakeStep(next_step_arguments, continuous_parameters, function_to_optimize, maximize);

        if(IsExitCriteriaFulfilled(next_step_arguments, arguments))
        {
            break;
        }

        // Check number of iterations
        if(i == max_iteration_number_)
        {
            std::cout<<" Minimun has not found";
        }

        // Make new basis by Gramm-Shmidt method
        CreateNewBasis();
        arguments = next_step_arguments;
    }

    continuous_parameters->SetValues(next_step_arguments);
}

HleborodovRosenbrockMethod* HleborodovRosenbrockMethod::Clone() const
{
    return new HleborodovRosenbrockMethod(precision_, max_iteration_number_, first_step_, max_step_);
}

#ifdef BUILD_WITH_MPI
void HleborodovRosenbrockMethod::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, precision_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, first_step_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, max_step_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, max_iteration_number_);
}

void HleborodovRosenbrockMethod::Receive(boost::mpi::communicator* communicator, int source)
{
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        precision_);
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        first_step_);
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        max_step_);
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        max_iteration_number_);
}
#endif

double HleborodovRosenbrockMethod::CountObjectiveFunctionValue(
    const IContinuousParameters* base_parameters,
    const std::vector<double>& parameters_values,
    const IObjectiveFunction& function_to_optimize,
    bool maximize)
{
    IContinuousParameters::shared_ptr parameters_clone(base_parameters->Clone());
    parameters_clone->SetValues(parameters_values);
    double counted_value = function_to_optimize(parameters_clone.get());
    return maximize ? (-counted_value) : counted_value;
}

void HleborodovRosenbrockMethod::InitializeBasisAndSteps()
{
    steps_array_ = vector<double> (dimension_,first_step_);

    basis_ = vector< vector<double> > (dimension_, vector<double> (dimension_, 0));

    // Initialize basis is Decart coordinate system
    for(size_t i = 0; i<dimension_; i++)
    {
        basis_[i][i] = 1;
    }
}

bool HleborodovRosenbrockMethod::IsExitCriteriaFulfilled(
    const vector<double>& arguments,
    const vector<double>& previous_step_arguments)
{
    bool escape = true;
    // check arguments increases to escape
    for(size_t j = 0; j<dimension_; j++)
    {
        if(fabs(arguments[j] - previous_step_arguments[j]) > precision_)
        {
            escape = false;
        }
    }
    return escape;
}

void HleborodovRosenbrockMethod::MakeStep(
    //TODO fix
    vector<double> &arguments,
    const IContinuousParameters* base_parameters,
    const IObjectiveFunction &function_to_optimize,
    bool maximize)
{
    double start_function_value = CountObjectiveFunctionValue(base_parameters, arguments, function_to_optimize, maximize);

    vector<double> tested_arguments(arguments);
    vector<double> tested_arguments2(arguments);

    /// Sort steps_array_ by descending for beter method speed
    std::sort(steps_array_.begin(), steps_array_.end(), std::greater<double>());

    for(size_t i = 0; i<dimension_; i++)
    {
        // make test step to minimize function in current direction
        // make it by each of coordinates
        MakeStepPerCoordinate(i, &tested_arguments);

        double counted_value = CountObjectiveFunctionValue(
            base_parameters,
            tested_arguments,
            function_to_optimize,
            maximize);

        if(start_function_value > counted_value)
        {
            steps_array_[i] *= arguments_increase_;
        }
        else
        {
            steps_array_[i] *= arguments_decrease_;
        }

        CorrectStep(i);

        MakeStepPerCoordinate(i, &tested_arguments2);

        tested_arguments = arguments;
    }

    arguments = tested_arguments2;
}

void HleborodovRosenbrockMethod::MakeStepPerCoordinate(int basis_index, vector<double>* arguments)
{
    for(size_t j = 0; j<dimension_; j++)
    {
        (*arguments)[j] += steps_array_[basis_index]*basis_[basis_index][j];
    }
}

void HleborodovRosenbrockMethod::CreateNewBasis()
{
    vector< vector<double> > matrix_of_coeff(dimension_, vector<double> (dimension_, 0));
    vector< vector<double> > unnormalized_basis(dimension_, vector<double> (dimension_, 0));

    for(size_t j = 0; j<dimension_; j++)
    {
        for(size_t i = j; i<dimension_; i++)
        {
            for(size_t k = 0; k<dimension_; k++)
            {
                matrix_of_coeff[j][k] += steps_array_[i]*basis_[i][k];
            }
        }
    }

    for(size_t i = 0; i<dimension_; i++)
    {
        for(size_t j = 0; j<dimension_; j++)
        {
            unnormalized_basis[i][j] = matrix_of_coeff[i][j];
        }
        basis_[0][i] = matrix_of_coeff[0][i];
    }

    NormalizeVector(basis_[0]);
    double temp;

    for(size_t j = 1; j<dimension_; j++)
    {
        for(size_t i = 0; i<j; i++)
        {
            temp = ScalarComposition(matrix_of_coeff[j],basis_[i]);
            for(size_t k = 0; k<dimension_; k++)
            {
                unnormalized_basis[j][k] -= temp*basis_[i][k];
            }
        }

        for(size_t k = 0; k<dimension_; k++)
        {
            basis_[j][k] = unnormalized_basis[j][k];
        }
        NormalizeVector(basis_[j]);
    }
}

void HleborodovRosenbrockMethod::NormalizeVector(vector<double> &target_vector)
{
    double temp = 0;
    for(size_t i = 0; i<dimension_; i++)
    {
        temp += target_vector[i]*target_vector[i];
    }
    temp = sqrt(temp);
    for(size_t i = 0; i<dimension_; i++)
    {
        if(temp != 0)
        {
            target_vector[i] /= temp;
        }
    }
}

double HleborodovRosenbrockMethod::ScalarComposition(
    const vector<double>& first_vector,
    const vector<double>& second_vector)
{
    double scalar_composition = 0;
    for(size_t i = 0; i<dimension_; i++)
    {
        scalar_composition += first_vector[i]*second_vector[i];
    }
    return scalar_composition;
}

void HleborodovRosenbrockMethod::CorrectStep(size_t step_index)
{
    if( fabs(steps_array_[step_index]) > max_step_)
    {
        steps_array_[step_index] =
            max_step_*steps_array_[step_index]/fabs(steps_array_[step_index]);
    }
}

}/* namespace optimization */
}/* namespace k52 */
