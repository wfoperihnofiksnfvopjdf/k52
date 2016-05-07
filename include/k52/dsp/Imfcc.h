#pragma once
//#include <k52/dsp/transform/fast_fourier_transform.h>
#include <vector>
#include <Math.h>
//#include <c:/k52/k52/include/k52/dsp/transform/fast_fourier_transform.h>
//#include <stdexcept>

//#include <boost/smart_ptr/shared_ptr.hpp>
#include <memory>
#include <complex>
#include <vector>
using ::std::complex;


namespace k52
{
	namespace dsp
	{

		class IMelFrequiencyCepstralCoefficients 
		{
		public:
			IMelFrequiencyCepstralCoefficients(const std::vector< double >& sequence);
			~IMelFrequiencyCepstralCoefficients();
			std::vector<double> GetMFCC();//получить все коэффициенты
			std::vector<double> GetMFCC(int); //получить определенное количество коэффициентов
			void Add_zvuk(const std::vector< double >& ); //вызывается в тех случаях когда нужно перепостроить коэффициенты по новым данным
			std::vector<double> Add_zvuk(const std::vector< double >&);
		private:

			
			const std::vector< double >& sequence;
			std::vector< std::complex< double > > ResultFFT;
			std::vector< double > MFCC;
			std::vector< double > Window; //может не нужно?
			void analising();
			std::vector<double> GetModulComplex(std::vector< std::complex<double>>);
		};

		class doWindow
		{
		public:
			std::vector< double > CreateWindow();
		};

		class MultiWindow:public doWindow
		{
		public:
			std::vector< double > Multiply_Window_Vektor(std::complex< double >);
		};

		class Sqr_Log
		{
		public:
			std::vector<double> GetSqrLog(std::vector< double>);
		};

		class CosPreobr
		{
		public:
			std::vector<double> getCosPreobr(std::vector<double>);
		};
	} // namespace dsp
} // namespace k52
