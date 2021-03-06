#ifndef IPARAMETERSPROCESSOR_H_
#define IPARAMETERSPROCESSOR_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/i_objective_function.h>

#include <vector>

namespace k52
{
namespace optimization
{

class IParametersProcessor
{
public:
    typedef boost::shared_ptr<IParametersProcessor> shared_ptr;

    IParametersProcessor() {}

    virtual IParameters::shared_ptr ProcessParameters(
        const IObjectiveFunction &function_to_optimize,
        const std::vector< IParameters::shared_ptr >& parameters,
        bool maximize) = 0;
private:
    DISALLOW_COPY_AND_ASSIGN(IParametersProcessor);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IPARAMETERSPROCESSOR_H_ */
