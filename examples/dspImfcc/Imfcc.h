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
			std::vector<double> GetMFCC();		 //�������� ��� ������������
			std::vector<double> GetMFCC(unsigned int);	 //�������� ������������ ���������� �������������
			void			    Add_zvuk(const std::vector< double >, size_t, bool); //���������� � ��� ������� ����� ����� ������������� ������������ �� ����� ������
			std::vector<double> Add_zvuk(const std::vector< double >, size_t);
		private:
			size_t SizeWindow;
			std::vector< double >EnergyTringle(std::vector< double >&, size_t);
			template <typename T > T FrecInMel(T);
			template <typename T > T MelInFrec(T);
			boost::shared_ptr <IFourierTransform> FFM;		//��������� �����
			const std::vector< double >& sequence;			//������ �����, ��������� ����� ��������� � Add_zvuk
			std::vector< double > MFCC;						//���� �����������, ��������� � �����������
			double epselon;									//������, ������������ � analizing
			void analising();								//������� ������ ������������
			std::vector<double> GetModulOfComplex(std::vector< std::complex<double>>); 
		};
	} // namespace dsp
} // namespace k52
