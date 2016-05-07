
#include "Imfcc.h"

namespace k52
{
	namespace dsp
	{
		IMelFrequiencyCepstralCoefficients::IMelFrequiencyCepstralCoefficients 	
			(const std::vector<double>& seque, IFourierTransform& Furie,double epsel):sequence(seque),FFM(Furie)
		{
			//��� ��������� ��������� ����� ��������������.
			epselon = epsel;//���������� ������
			Add_zvuk(sequence);//�������� �����������
		};
		IMelFrequiencyCepstralCoefficients::~IMelFrequiencyCepstralCoefficients () 
		{		
			MFCC.erase;
			Window.erase;
			FFM.~IFourierTransform();
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
			for (int i = 0;i < MFCC.size;i++)
			if (MFCC[i]<epselon)
			{
				bool verno = false;
				for (int j = i + 1;j < MFCC.size;j++)
					if (MFCC[j]>epselon)
					{
						verno = true;
						break;
					}
				if (verno == false)
				{
					MFCC.resize(i - 1);
					break;
				}
			}
		};
		//������
		std::vector <double> IMelFrequiencyCepstralCoefficients::	GetModulOfComplex(std::vector< std::complex<double>> vhod) 
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				vuhod[i] = vhod[i].imag*vhod[i].imag + vhod[i].real*vhod[i].real;
			return vuhod;
		};
		//������
		void IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >& vhod,bool prost)//������ ������
		{
			std::vector< std::complex<double>> WithFurie(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				WithFurie[i] = vhod[i];
			//����� �����
			
			WithFurie =FFM.Transform(WithFurie);//WTF why incoming in complex?!
			std::vector <double> FurieDouble=GetModulOfComplex(WithFurie);//����� ������ ��������� ����������� �������
			//������ MFCC � ���� �����
			MFCC = Multiply_Window_Vektor(FurieDouble); //�������� �� ����, ��� ��� �� � ������� � ���������
			MFCC = GetSqrLog(MFCC);//����� ������� ��������
			MFCC = getCosPreobr(MFCC);//����� ���������� ��������������
			
			//����� � ������� ������
			WithFurie.erase;
			sequence.clear;
		};
		std::vector<double> IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >&vhod) 
		{
			Add_zvuk(vhod,true);
			analising();
			return MFCC;
		};
		//������
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
		std::vector< double > MultiWindow::Multiply_Window_Vektor(std::vector< double > vhod)//����������� ��������� � ������� ����������� ���� ����.
		{
			std::vector <double> a(3);
			return a;
		};
		//--------------------------------------------------------------------------------------------------


	} // namespace dsp
} // namespace k52