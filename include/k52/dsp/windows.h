#include <cmath>
#include <vector>

namespace k52
{
namespace dsp
{
	class Window
	{
	public:
		template <typename T> double tringleWindow(T, T, T);
	};
} // namespace dsp
} // namespace k52