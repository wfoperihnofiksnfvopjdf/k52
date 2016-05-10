#pragma once


#include <Math.h>
#include <cmath>
#include <vector>
#include <complex>
#include <c:/k52/k52/include/k52/dsp/transform/i_fourier_transform.h>
#include <memory>


namespace k52
{
	namespace dsp
	{
		class IMelFrequiencyCepstralCoefficients :public TringleWindow,public CosPreobr
		{
		public:
			IMelFrequiencyCepstralCoefficients(const std::vector< double >&, IFourierTransform& ,double);
			~IMelFrequiencyCepstralCoefficients();
			std::vector<double> GetMFCC();		 //�������� ��� ������������
			std::vector<double> GetMFCC(int);	 //�������� ������������ ���������� �������������
			void			    Add_zvuk(const std::vector< double >& , bool); //���������� � ��� ������� ����� ����� ������������� ������������ �� ����� ������
			std::vector<double> Add_zvuk(const std::vector< double >&,int);
		private:
			std::vector< double >EnergyTringle(std::vector< double >);
			template <typename T > T FrecInMel(T);
			template <typename T > T MelInFrec(T);
			double epselon;							//������, ������������ � analizing
			shared_ptr <IFourierTransform> FFM;		//��������� �����
			const std::vector< double >& sequence;	//������ �����, ��������� ����� ��������� � Add_zvuk
			std::vector< double > MFCC;				//���� �����������, ��������� � �����������
			
			//����� �� ����� (���� ������ � ����������� �� �������� ������� ������ ���� ������ ��� ������� �� �������� ������)? ���� � �����������
			void analising();
			std::vector<double> GetModulOfComplex(std::vector< std::complex<double>>);
		};

		class TringleWindow
		{
		public:
			template <typename T> double TringleWindow::tringleWindow(T, T, T);
		};



		class CosPreobr
		{
		public:
			std::vector<double> getCosPreobr1(std::vector<double>);
			std::vector<double> getCosPreobr2(std::vector<double>);
			std::vector<double> getCosPreobr3(std::vector<double>);
			std::vector<double> getCosPreobr4(std::vector<double>);
		};
	} // namespace dsp
} // namespace k52
