#include <k52/dsp/transform/fast_fourier_transform.h>
//#include <std::Math.h>



namespace k52
{
	namespace dsp
	{

		class MelFrequiencyCepstralCoefficients : public FastFourierTransform
		{
		public:
			MelFrequiencyCepstralCoefficients(const std::vector< double >& sequence);
			~MelFrequiencyCepstralCoefficientsFCC();
		};

	} // namespace dsp
} // namespace k52