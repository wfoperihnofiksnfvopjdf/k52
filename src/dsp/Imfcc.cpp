
#include "Imfcc.h"

namespace k52
{
	namespace dsp
	{
		IMelFrequiencyCepstralCoefficients::IMelFrequiencyCepstralCoefficients 	
			(const std::vector<double>& seque, IFourierTransform& Furie,double epsel):sequence(seque),FFM(Furie)
		{
			//уже сохранили интерфейс фурье преобразования.
			epselon = epsel;//допустимая ошибка
			Add_zvuk(sequence);//получаем коэфициенты
		};
		IMelFrequiencyCepstralCoefficients::~IMelFrequiencyCepstralCoefficients () 
		{		
			MFCC.erase;
			Window.erase;
			FFM.~IFourierTransform();
		};
		
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC()//сделан				
		{
			return GetMFCC(MFCC.size);
		};	
		//сделан
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC(int i)//сделан		
		{
			if (i > MFCC.size)
				i = MFCC.size;
			std::vector <double> a(i);
			for (int j = 0;j < MFCC.size;j++)
				a[j] = MFCC[i];
			return a;
		}; 
		//сделан
		void		 		 IMelFrequiencyCepstralCoefficients::	analising()//аналитика высчитывающая что коэффициенты с определенного места являются лишними (допустим нули)
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
		//сделан
		std::vector <double> IMelFrequiencyCepstralCoefficients::	GetModulOfComplex(std::vector< std::complex<double>> vhod) 
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				vuhod[i] = vhod[i].imag*vhod[i].imag + vhod[i].real*vhod[i].real;
			return vuhod;
		};
		//сделан
		void IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >& vhod,bool prost)//сердце метода
		{
			std::vector< std::complex<double>> WithFurie(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				WithFurie[i] = vhod[i];
			//фурье метод
			
			WithFurie =FFM.Transform(WithFurie);//WTF why incoming in complex?!
			std::vector <double> FurieDouble=GetModulOfComplex(WithFurie);//берем модуль элементов полученного массива
			//охапка MFCC и плов готов
			MFCC = Multiply_Window_Vektor(FurieDouble); //умножаем на окно, где его же и находим и сохраняем
			MFCC = GetSqrLog(MFCC);//берем квадрат логорифм
			MFCC = getCosPreobr(MFCC);//берем косинусное преобразование
			
			//конец и очистка мусора
			WithFurie.erase;
			sequence.clear;
		};
		std::vector<double> IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >&vhod) 
		{
			Add_zvuk(vhod,true);
			analising();
			return MFCC;
		};
		//сделан
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
		std::vector< double > MultiWindow::Multiply_Window_Vektor(std::vector< double > vhod)//Наследуется интерфейс в котором сохраняется коэф окна.
		{
			std::vector <double> a(3);
			return a;
		};
		//--------------------------------------------------------------------------------------------------


	} // namespace dsp
} // namespace k52