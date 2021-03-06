#include <k52/optimization/params/composite_discrete_parameters.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

CompositeDiscreteParameters* CompositeDiscreteParameters::Clone() const
{
    initialization_checker_.InitializationCheck();

    CompositeDiscreteParameters* clone = new CompositeDiscreteParameters();
    clone->Initialize(parameters_set_);
    return clone;
}

bool CompositeDiscreteParameters::HasSameMetaParameters(const IDiscreteParameters* parameters) const
{
    throw std::runtime_error("HasSameMetaParameters is not implemented in CompositeDiscreteParameters");
}

bool CompositeDiscreteParameters::CheckConstraints() const
{
    initialization_checker_.InitializationCheck();

    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        if(!parameters_set_[i]->CheckConstraints())
        {
            return false;
        }
    }
    return true;
}

void CompositeDiscreteParameters::SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const
{
    initialization_checker_.InitializationCheck();

    size_t chromosome_size = to - from;

    this->CheckForConstChromosomeSize(chromosome_size);

    ChromosomeType::iterator current_from = from;

    for(size_t i = 0; i < parameters_set_.size(); i++)
    {
        size_t parameter_chromosome_size = parameters_set_[i]->GetChromosomeSize();

        ChromosomeType::iterator current_to = current_from + parameter_chromosome_size;

        parameters_set_[i]->SetChromosome(current_from, current_to);

        current_from = current_to;
    }
}

void CompositeDiscreteParameters::SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to)
{
    initialization_checker_.InitializationCheck();

    size_t chromosome_size = to - from;

    this->CheckForConstChromosomeSize(chromosome_size);

    ChromosomeType::const_iterator current_from = from;

    for(size_t i = 0; i < parameters_set_.size(); i++)
    {
        size_t parameter_chromosome_size = parameters_set_[i]->GetChromosomeSize();

        ChromosomeType::const_iterator current_to = current_from + parameter_chromosome_size;

        parameters_set_[i]->SetFromChromosome(current_from, current_to);

        current_from = current_to;
    }
}

void CompositeDiscreteParameters::Initialize(const std::vector<IDiscreteParameters::shared_ptr>& parameters)
{
    parameters_set_ = std::vector<IDiscreteParameters::shared_ptr>(parameters.size());

    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        parameters_set_[i] = IDiscreteParameters::shared_ptr(parameters[i]->Clone());
    }

    this->SetConstChromosomeSize( CountTotalChromosomeSize() );

    initialization_checker_.SetInitialized();
}

void CompositeDiscreteParameters::Initialize(const IDiscreteParameters::shared_ptr& sample_parameter, size_t number_of_parameters)
{
    parameters_set_ = std::vector<IDiscreteParameters::shared_ptr>(number_of_parameters);

    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        parameters_set_[i] = IDiscreteParameters::shared_ptr(sample_parameter->Clone());
    }

    this->SetConstChromosomeSize( CountTotalChromosomeSize() );

    initialization_checker_.SetInitialized();
}

size_t CompositeDiscreteParameters::GetNumberOfParameters() const
{
    initialization_checker_.InitializationCheck();

    return parameters_set_.size();
}

const IDiscreteParameters::shared_ptr CompositeDiscreteParameters::GetParameter(size_t index) const
{
    initialization_checker_.InitializationCheck();

    if(index+1 > parameters_set_.size())
    {
        throw std::out_of_range("index in getParameter method is out of range");
    }

    return parameters_set_[index];
}

size_t CompositeDiscreteParameters::CountTotalChromosomeSize() const
{
    size_t total_chromosome_size = 0;
    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        total_chromosome_size += parameters_set_[i]->GetChromosomeSize();
    }
    return total_chromosome_size;
}

}/* namespace optimization */
}/* namespace k52 */

