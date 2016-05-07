#include "stdafx.h"
#include "Imfcc.h"
//#include <c:/k52/k52/include/k52/dsp/transform/fast_fourier_transform.h>


namespace k52
{
	namespace dsp
	{
		IMelFrequiencyCepstralCoefficients::IMelFrequiencyCepstralCoefficients 	(const std::vector<double>& seque):sequence(seque)
		{
			//��������� ��������� ����� ��������������.
			Add_zvuk(sequence);
		};
		IMelFrequiencyCepstralCoefficients::		~IMelFrequiencyCepstralCoefficients () 
		{
			
			std::vector< double > MFCC;
			std::vector< double > Window; //����� �� �����?
		};
		
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC()//������				
		{
			return GetMFCC(MFCC.size);
		};	
		//������
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC(int i)//������		
		{
			if (i > MFCC.size)
				i = MFCC.size;
			std::vector <double> a(i);
			for (int j = 0;j < MFCC.size;j++)
				a[j] = MFCC[i];
			return a;
		}; 
		//������
		void		 		 IMelFrequiencyCepstralCoefficients::	analising()//��������� ������������� ��� ������������ � ������������� ����� �������� ������� (�������� ����)
		{
		};
		std::vector <double> IMelFrequiencyCepstralCoefficients::	GetModulComplex(std::vector< std::complex<double>> vhod) 
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				vuhod[i] = vhod[i].imag*vhod[i].imag + vhod[i].real*vhod[i].real;
			return vuhod;
		};
		//������
		void IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >& vhod)
		{
			//����� �����
			
			ResultFFT.erase;
			//�����
			sequence.clear;
		};
		std::vector<double> IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >&vhod) 
		{
			Add_zvuk(vhod);
			return MFCC;
		};
		//--------------------------------------------------------------------------------------------------
		std::vector<double> CosPreobr::getCosPreobr(std::vector<double> vhod)
		{
			std::vector <double> a(3);
			return a;
		};
		//--------------------------------------------------------------------------------------------------
		std::vector <double> Sqr_Log::GetSqrLog( std::vector<double> vhod) 
		{
			std::vector <double> a(3);
			return a;
		};
		//--------------------------------------------------------------------------------------------------
		std::vector< double > doWindow::CreateWindow() 
		{
			std::vector <double> a(3);
			return a;
		};
		//--------------------------------------------------------------------------------------------------
		std::vector< double > MultiWindow::Multiply_Window_Vektor(std::complex< double > vhod)
		{
			std::vector <double> a(3);
			return a;
		};
		//--------------------------------------------------------------------------------------------------


	} // namespace dsp
} // namespace k52