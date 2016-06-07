#include "Imfcc.h"

namespace k52
{
	namespace dsp
	{
		IMelFrequiencyCepstralCoefficients::IMelFrequiencyCepstralCoefficients
			(const std::vector<double> seque,boost::shared_ptr <IFourierTransform> Furie,double epsel):sequence(seque),SizeWindow(4)
		{

			FFM = Furie;//сохранили интерфейс фурье преобразовани€.
			epselon = epsel;//допустима€ ошибка
			Add_zvuk(sequence,SizeWindow);//получаем коэфициенты
		};
		IMelFrequiencyCepstralCoefficients::~IMelFrequiencyCepstralCoefficients () 
		{		
			//MFCC.erase;
			FFM->~IFourierTransform();
		};
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC()//сделан				
		{
			return GetMFCC(MFCC.size());
		};	
		std::vector <double> IMelFrequiencyCepstralCoefficients::GetMFCC(size_t i)
		{
			if (i > MFCC.size())
				i = MFCC.size();
			std::vector <double> a(i);
			for (size_t j = 0;j < MFCC.size();j++)
				a[j] = MFCC[i];
			return a;
		}; 
		//сделан
		void IMelFrequiencyCepstralCoefficients::	analising()
		{
			size_t N = MFCC.size();
			for (size_t i = 0;i < N;i++)
			if (MFCC[i]<epselon)
			{
				bool verno = false;

				for (size_t j = i + 1;j < N ;j++)
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
		}; //аналитика высчитывающа€ что коэффициенты с определенного места €вл€ютс€ лишними (допустим нули)
		//сделан
		std::vector <double> IMelFrequiencyCepstralCoefficients::	GetModulOfComplex(std::vector< std::complex<double>> inputData) 
		{
			size_t N = inputData.size();
			std::vector <double> outputData(N);
			for (size_t i = 0;i < N;i++)
				outputData[i] = abs(inputData[i]);
			return outputData;
		};
		//сделан
		template <typename T> T  IMelFrequiencyCepstralCoefficients::FrecInMel(T f)
		{
			return (T)(1127.01048*log(1 + f / 700));//(T)(1127.01048*log(1 + f / 700));
		};
		//сделан
		template <typename T> T IMelFrequiencyCepstralCoefficients::MelInFrec(T m)
		{
			return (T)(700 * (exp(m / 1127.01048) - 1));//(T)(700 * (exp(m / 1127.01048) - 1));
		};
		//сделан
		void IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double > vhod, size_t rasOk,/*размер окна*/bool prost)//сердце метода
		{
			size_t N = vhod.size();
			std::vector< std::complex<double>> M(N);
			for (size_t i = 0;i < N ;i++)
				M[i] = vhod[i];
			std::vector< std::complex<double>> WithFurie = FFM->Transform(M);//vhod);//WTF? why incoming in complex?!
			std::vector <double> FurieDouble=GetModulOfComplex(WithFurie);//берем модуль элементов полученного массива
		

			//охапка MFCC и плов готов
			MFCC = EnergyTringle(FurieDouble,rasOk); //умножаем на окно, где его же и находим и сохран€ем
			MFCC = getCosPreobr2(MFCC);//берем второе косинусное преобразование
			
			//конец и очистка мусора
//			WithFurie.erase;
			//sequence.clear;
		};
		std::vector<double> IMelFrequiencyCepstralCoefficients::Add_zvuk(const std::vector< double >vhod, size_t RasmOkna)
		{
			Add_zvuk(vhod, RasmOkna,true);
			analising();
			return MFCC;
		};
		std::vector< double >IMelFrequiencyCepstralCoefficients::EnergyTringle(std::vector< double >& vhod, size_t rasOk)
		{
			size_t N = vhod.size();
			size_t KolOkon = (size_t)(FrecInMel(N) / rasOk-1);//находим количество окон
			std::vector <double> Energia(KolOkon);
			std::vector <double> mel(N);
			for ( double i = 1;i <= N;i++)
				mel[i-1] = FrecInMel(i);
			size_t nachaloF = 0,sredina;
			for (size_t i = 0;i<KolOkon;i++)
			{
				double sum = 0;
				size_t j;
				for (j = mel[nachaloF]+1; mel[j] < mel[nachaloF] + rasOk * 2 ; j++);
				for ( sredina = nachaloF + 1;mel[sredina]<mel[nachaloF]+(mel[nachaloF]-mel[j])/2;sredina++);
				for (size_t u=nachaloF;u<=j;u++)
					sum += vhod[u] * vhod[u] * tringleWindow(mel[nachaloF] , mel[j] , mel[u]);
				nachaloF = j;
				Energia[i] = log(sum);
			}

			return Energia;
		};
		
	} // namespace dsp
} // namespace k52