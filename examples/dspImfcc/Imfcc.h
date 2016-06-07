#pragma once


#include <Math.h>
#include <cmath>
#include <memory>
#include <k52/dsp/transform/i_fourier_transform.h>
#include "cosin_preobrasovanie.h"
#include "windows.h"

namespace k52
{
	namespace dsp
	{
		class IMelFrequiencyCepstralCoefficients :public Window,public CosPreobr
		{
		public:
			IMelFrequiencyCepstralCoefficients(const std::vector< double >, boost::shared_ptr <IFourierTransform>,double);
			~IMelFrequiencyCepstralCoefficients();
			std::vector<double> GetMFCC();		 //получить все коэффициенты
			std::vector<double> GetMFCC(unsigned int);	 //получить определенное количество коэффициентов
			void			    Add_zvuk(const std::vector< double >, size_t, bool); //вызывается в тех случаях когда нужно перепостроить коэффициенты по новым данным
			std::vector<double> Add_zvuk(const std::vector< double >, size_t);
		private:
			size_t SizeWindow;
			std::vector< double >EnergyTringle(std::vector< double >&, size_t);
			template <typename T > T FrecInMel(T);
			template <typename T > T MelInFrec(T);
			boost::shared_ptr <IFourierTransform> FFM;		//интерфейс фурье
			const std::vector< double >& sequence;			//вектор звука, удаляется после обработки в Add_zvuk
			std::vector< double > MFCC;						//сами коэфициенты, удаляется в деструкторе
			double epselon;									//ошибка, используется в analizing
			void analising();								//удаляем пустые коэффициенты
			std::vector<double> GetModulOfComplex(std::vector< std::complex<double>>); 
		};
	} // namespace dsp
} // namespace k52
