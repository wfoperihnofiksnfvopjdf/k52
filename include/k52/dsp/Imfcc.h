#pragma once


#include <Math.h>
#include <c:/k52/k52/include/k52/dsp/transform/i_fourier_transform.h>
#include <memory>

using ::std::complex;


namespace k52
{
	namespace dsp
	{

		class IMelFrequiencyCepstralCoefficients 
		{
		public:
			IMelFrequiencyCepstralCoefficients(const std::vector< double >&, IFourierTransform& ,double);
			~IMelFrequiencyCepstralCoefficients();
			std::vector<double> GetMFCC();//получить все коэффициенты
			std::vector<double> GetMFCC(int); //получить определенное количество коэффициентов
			void Add_zvuk(const std::vector< double >& , bool); //вызывается в тех случаях когда нужно перепостроить коэффициенты по новым данным
			std::vector<double> Add_zvuk(const std::vector< double >&);
		private:

			double epselon;//используется в analizing
			IFourierTransform& FFM;
			const std::vector< double >& sequence;//вектор звука, удаляется после обработки в Add_zvuk
			std::vector< std::complex< double > > ResultFFT;//итог преобразования фурье, удаляется после обработки в Add_zvuk
			std::vector< double > MFCC; //сами коэф, удал в деструкторе
			std::vector< double > Window; //может не нужно? удал в деструкторе
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
