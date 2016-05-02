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
			std::vector<double> GetMFCC();
			std::vector<double> GetMFCC(int );
		private:

			const std::vector< double >& sequence
			std::vector< std::complex< double > > ResultFFT;
			std::vector< double > MFCC;
			std::vector< double > Window;
			std::vector<double > CreateWindow();
			std::vector<double> Multiply_Window_Vektor();
			void analising();
		};

	} // namespace dsp
} // namespace k52