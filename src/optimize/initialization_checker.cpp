#include <optimize/initialization_checker.h>

#include <stdexcept>

namespace k52
{
namespace optimize
{

InitializationChecker::InitializationChecker()
{
    was_initialized_ = false;
}

void InitializationChecker::InitializationCheck() const
{
    if(!was_initialized_)
    {
        throw std::logic_error("Object was used without being initialized");
    }
}

void InitializationChecker::SetInitialized()
{
    if(!was_initialized_)
    {
        was_initialized_ = true;
    }
    else
    {
        throw std::logic_error("Another initialization happened");
    }
}

}/* namespace optimize */
}/* namespace k52 */
