//#include "stdafx.h"
#include "Imfcc.h"
#include <c:/k52/k52/include/k52/dsp/transform/fast_fourier_transform.h>


namespace k52
{
	namespace dsp
	{
		MelFrequiencyCepstralCoefficients::		MelFrequiencyCepstralCoefficients  () {};
		MelFrequiencyCepstralCoefficients::		MelFrequiencyCepstralCoefficients  (const std::vector<double>& sequence) {};
		MelFrequiencyCepstralCoefficients::		~MelFrequiencyCepstralCoefficients () {};
		
		std::vector <double> MelFrequiencyCepstralCoefficients::	GetMFCC()					{};
		std::vector <double> MelFrequiencyCepstralCoefficients::	GetMFCC(int i)				{};
		std::vector <double> MelFrequiencyCepstralCoefficients::	CreateWindow()				{};
		std::vector <double> MelFrequiencyCepstralCoefficients::	Multiply_Window_Vektor()	{};
		void		 		 MelFrequiencyCepstralCoefficients::	analising()					{};
		//--------------------------------------------------------------------------------------------------
		std::vector<double> ModulOFComplex::GetModul(std::vector< std::complex<double>> vhod) {};
		//--------------------------------------------------------------------------------------------------

	} // namespace dsp
} // namespace k52