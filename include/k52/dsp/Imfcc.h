#pragma once


#include <Math.h>
#include <c:/k52/k52/include/k52/dsp/transform/i_fourier_transform.h>
#include <memory>

using ::std::complex;


namespace k52
{
	namespace dsp
	{

		class IMelFrequiencyCepstralCoefficients :public MultiWindow, public Sqr_Log,public CosPreobr
		{
		public:
			IMelFrequiencyCepstralCoefficients(const std::vector< double >&, IFourierTransform& ,double);
			~IMelFrequiencyCepstralCoefficients();
			std::vector<double> GetMFCC();//�������� ��� ������������
			std::vector<double> GetMFCC(int); //�������� ������������ ���������� �������������
			void Add_zvuk(const std::vector< double >& , bool); //���������� � ��� ������� ����� ����� ������������� ������������ �� ����� ������
			std::vector<double> Add_zvuk(const std::vector< double >&);
		private:

			double epselon;//������������ � analizing
			IFourierTransform& FFM;
			const std::vector< double >& sequence;//������ �����, ��������� ����� ��������� � Add_zvuk
			std::vector< double > MFCC; //���� �����������, ��������� � �����������
			std::vector< double > Window; 
			//����� �� ����� (���� ������ � ����������� �� �������� ������� ������ ���� ������ ��� ������� �� �������� ������)? ���� � �����������
			void analising();
			std::vector<double> GetModulOfComplex(std::vector< std::complex<double>>);
		};

		class doWindow
		{
		public:
			std::vector< double > CoefFunctionOfWindow;
			std::vector< double > CreateWindow();
		};

		class MultiWindow:public doWindow
		{
		public:
			std::vector< double > Multiply_Window_Vektor(std::vector< double >);
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
