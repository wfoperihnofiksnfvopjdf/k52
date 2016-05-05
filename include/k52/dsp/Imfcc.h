#pragma once
//#include <k52/dsp/transform/fast_fourier_transform.h>
#include <vector>
#include <Math.h>
#include <c:/k52/k52/include/k52/dsp/transform/fast_fourier_transform.h>
#include <stdexcept>

//#include <boost/smart_ptr/shared_ptr.hpp>

#include <complex>
#include <vector>
using ::std::complex;


namespace k52
{
	namespace dsp
	{

		class MelFrequiencyCepstralCoefficients 
		{
		public:

			MelFrequiencyCepstralCoefficients(const std::vector< double >& sequence);
			~MelFrequiencyCepstralCoefficients();
			std::vector<double> GetMFCC();
			std::vector<double> GetMFCC(int);

		private:

			const std::vector< double >& sequence;
			std::vector< std::complex< double > > ResultFFT;
			std::vector< double > MFCC;
			std::vector< double > Window;
			std::vector<double > CreateWindow();
			std::vector<double> Multiply_Window_Vektor();
			void analising();
		};

		class ModulOFComplex
		{
		    public:

			ModulOFComplex();
			std::vector<double> GetModul(std::vector< std::complex<double>>);
		};
	} // namespace dsp
} // namespace k52
