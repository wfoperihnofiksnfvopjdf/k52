#include <k52/dsp/windows.h>


namespace k52
{
namespace dsp
{
	template <typename T> double Window::tringleWindow(T k1, T k3, T tt)
	{
		T result = 0;
		T k2 = (k3 - k1) / 2 + k1;
		if ((tt <= k1) || (tt >= k3))
			result = 0;
		else if (tt < k2)
			result = (tt - k1) / (k2 - k1);
		else result = (k3 - tt) / (k3 - k2);
		return result;
	};

} // namespace dsp
} // namespace k52
