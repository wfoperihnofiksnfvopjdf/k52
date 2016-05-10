#include "Imfcc.h"
//#include "Math.h"


namespace k52
{
	namespace dsp
	{
		IMelFrequiencyCepstralCoefficients::IMelFrequiencyCepstralCoefficients
			(const std::vector<double>& seque, IFourierTransform & Furie,double epsel):sequence(seque),FFM(Furie)
		{
			//уже сохранили интерфейс фурье преобразования.
			epselon = epsel;//допустимая ошибка
			Add_zvuk(sequence,4);//получаем коэфициенты
		};
		IMelFrequiencyCepstralCoefficients::~IMelFrequiencyCepstralCoefficients () 
		{		
			MFCC.erase;
			//FFM.
		};
		
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC()//сделан				
		{
			return GetMFCC(MFCC.size);
		};	
		//сделан
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC(int i)		
		{
			if (i > MFCC.size)
				i = MFCC.size;
			std::vector <double> a(i);
			for (int j = 0;j < MFCC.size;j++)
				a[j] = MFCC[i];
			return a;
		}; 
		//сделан
		void IMelFrequiencyCepstralCoefficients::	analising()//аналитика высчитывающая что коэффициенты с определенного места являются лишними (допустим нули)
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
		template <typename T> IMelFrequiencyCepstralCoefficients::FrecInMel(T f)
		{
			return (T)(1127.01048*log(1 + f / 700));
		};
		//сделан
		template <typename T> IMelFrequiencyCepstralCoefficients::MelInFrec(T m)
		{
			return (T)(700 * (exp(m / 1127.01048) - 1));
		};
		//сделан
		void IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >& vhod, int rasOk,/*размер окна*/,bool prost)//сердце метода
		{
			std::vector< std::complex<double>> WithFurie=FFM.Transform(vhod);//WTF? why incoming in complex?!
			std::vector <double> FurieDouble=GetModulOfComplex(WithFurie);//берем модуль элементов полученного массива
		

			//охапка MFCC и плов готов
			MFCC = EnergyTringleMFCC(FurieDouble,KolOkon); //умножаем на окно, где его же и находим и сохраняем
			MFCC = getCosPreobr2(MFCC);//берем второе косинусное преобразование
			
			//конец и очистка мусора
			WithFurie.erase;
			sequence.clear;
		};
		std::vector<double> IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >&vhod,int RasmOkna) 
		{
			Add_zvuk(vhod, RasmOkna,true);
			analising();
			return MFCC;
		};
		//сделан
		//--------------------------------------------------------------------------------------------------
		std::vector<double> CosPreobr::getCosPreobr1(std::vector<double> vhod)
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
			{
				if (i%2==0)
					vuhod[i] = 0.5*(vhod[0] + vhod[vhod.size - 1]);
				else
				vuhod[i] = 0.5*(vhod[0]+(-1)*vhod[vhod.size-1]);
				for (int j = 1;j < vhod.size - 1;j++)
					vuhod[i] += vhod[j]*cos(14159265358979323846 * j*i / (vhod.size - 1));
			}
			return vuhod;
		};
		std::vector<double> CosPreobr::getCosPreobr2(std::vector<double> vhod)
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				for (int j = 0;j < vhod.size;j++)
					vuhod[i] += vhod[j] * cos(3.14159265358979323846*i*(j+0.5)/vhod.size);
				return vuhod;
		};
		std::vector<double> CosPreobr::getCosPreobr3(std::vector<double> vhod)
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
			{
				vuhod[i] = 0.5*vhod[0];
				for (int j = 1;j < vhod.size-1;j++)
					vuhod[i] += vhod[j] * cos(3.14159265358979323846*j*(i+0.5) / vhod.size);
			}
			return vuhod;
		};
		std::vector<double> CosPreobr::getCosPreobr4(std::vector<double> vhod)
		{
			std::vector <double> vuhod(vhod.size);
			for (int i = 0;i < vhod.size;i++)
				for (int j = 0;j < vhod.size;j++)
					vuhod[i] += vhod[j] * cos(3.14159265358979323846*(i+0.5)*(j + 0.5) / vhod.size);
			return vuhod;
		};
		//сделано
		//--------------------------------------------------------------------------------------------------
		template <typename T> double TringleWindow::tringleWindow(T k1,T k3,T tt)
		{
			T result = 0;
			T k2 = (k3 - k1) / 2 + k1;
			if ((tt <= k1) || (tt >= k3))
				result = 0;
			else if (tt < k2)
				result = (tt - k1) / (k2 - k1);
			else result = (k3-tt) / (k3-k2);
			return result;
		};
		//--------------------------------------------------------------------------------------------------
		std::vector< double >IMelFrequiencyCepstralCoefficients::EnergyTringle(std::vector< double > vhod, int rasOk)
		{
			int KolOkon = FrecInMel(vhod.size) / rasOk-1;//находим количество окон
			std::vector <double> Energia(KolOkon);
			std::vector <double> mel(vhod.size);
			for (int i = 1;i <= vhod.size;i++)
				mel = FrecInMel(i);
			//double nachaloM = mel[0];
			int nachaloF = 0,sredina;
			for (int i = 0;i<KolOkon;i++)
			{
				double sum = 0;
				int j;
				for (j = mel[nachaloF]+1; mel[j] < mel[nachaloF] + rasOk * 2 ; j++);
				for ( sredina = nachaloF + 1;mel[sredina]<mel[nachaloF]+(mel[nachaloF]-mel[j])/2;sredina++);
				for (int u=nachaloF;u<=j;u++)
					sum += vhod[u] * vhod[u] * tringleWindow(mel[nachaloF] , mel[j] , mel[u]);
				nachaloF = j;
				Energia[i] = log(sum);
			}


		};
		
		//--------------------------------------------------------------------------------------------------


	} // namespace dsp
} // namespace k52