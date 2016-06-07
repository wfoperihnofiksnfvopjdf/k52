#include <iostream>
#include "Imfcc.h"

//using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "isabella" << std::endl;

	return 0;
}
	/*
	time_t begin, end;
	cout << "Begin" << endl;

	int populationSize = 300;
	int numberOfIterations = 10;
	int elitismPairs = 25;
	double mutation = 0.000001;
	double cacheLimitInMegabytes = 1;
	bool usePrintStatistics = false;

	/////////////Genetic Algrythm///////////////
	//DoubleParametersArray parameters(GlobalMinValue, GlobalMaxValue, GlobalPrecision, GlobalNumberOfParameters);
	//ExactDiscreteObjectiveFunction of;

	//TODO currently have to manually all nesessary objects

	//TODO FIX
	/*
	try
	{
		//ga->SetInitialParameters(GetInitialParameters(populationSize));
		ga->Optimize(of, &parameters, true);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return -1;
	}

	vector<double> values = parameters.get_values();

	for(size_t i=0; i<values.size(); i++)
	{
		cout<<i<<"-th parameter = "<<values[i]<<endl;
	}

	cout<<"Fitness = "<<of(&parameters)<<endl;
	/////////////Genetic Algrythm end///////////////

	time(&end);
	cout << "Time elapsed: " << difftime(end, begin) << " seconds "<< endl;
	return 0;
}*/
