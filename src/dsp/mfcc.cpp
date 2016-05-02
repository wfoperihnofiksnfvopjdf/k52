#include <k52/dsp/mfcc.h>

namespace k52
{
	namespace dsp
	{
		class MelFrequiencyCepstralCoefficients::MelFrequiencyCepstralCoefficients {};
		MelFrequiencyCepstralCoefficients: MelFrequiencyCepstralCoefficients(const std::vector< double >& sequence) {};
		MelFrequiencyCepstralCoefficients:~MelFrequiencyCepstralCoefficientsFCC() {};
		MelFrequiencyCepstralCoefficients:std::vector<double> GetMFCC() {};
		MelFrequiencyCepstralCoefficients:std::vector<double> GetMFCC(int i) {};
		MelFrequiencyCepstralCoefficients:std::vector<double > CreateWindow() {};
		MelFrequiencyCepstralCoefficients:std::vector<double> Multiply_Window_Vektor() {};
		MelFrequiencyCepstralCoefficients:void analising();

	} // namespace dsp
} // namespace k52