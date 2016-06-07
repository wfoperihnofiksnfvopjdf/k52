#include "cosin_preobrasovanie.h"

namespace k52
{
namespace dsp
{
	std::vector<double> CosPreobr::getCosPreobr1(std::vector<double> inputData)
	{
		size_t N = inputData.size();
		std::vector <double> outputData(N);
		for (size_t i = 0;i < N;i++)
		{
			if (i % 2 == 0)
				outputData[i] = 0.5*(inputData[0] + inputData[N - 1]);
			else
				outputData[i] = 0.5*(inputData[0] + (-1)*inputData[N - 1]);
			for (size_t j = 1;j < N - 1;j++)
				outputData[i] += inputData[j] * cos(14159265358979323846 * j*i / (N - 1));
		}
		return outputData;
	};

	std::vector<double> CosPreobr::getCosPreobr2(std::vector<double> inputData)
	{
		size_t N = inputData.size();
		std::vector <double> outputData(N);
		for (size_t i = 0;i < N;i++)
			for (size_t j = 0;j < N;j++)
				outputData[i] += inputData[j] * cos(3.14159265358979323846*i*(j + 0.5) / N);
		return outputData;
	};

	std::vector<double> CosPreobr::getCosPreobr3(std::vector<double> inputData)
	{
		size_t N = inputData.size();
		std::vector <double> outputData(N);
		for (size_t i = 0;i < N;i++)
		{
			outputData[i] = 0.5*inputData[0];
			for (size_t j = 1;j < N - 1;j++)
				outputData[i] += inputData[j] * cos(3.14159265358979323846*j*(i + 0.5) / N);
		}
		return outputData;
	};

	std::vector<double> CosPreobr::getCosPreobr4(std::vector<double> inputData)
	{
		size_t N = inputData.size();
		std::vector <double> outputData(N);
		for (size_t i = 0;i < N;i++)
			for (size_t j = 0;j < N;j++)
				outputData[i] += inputData[j] * cos(3.14159265358979323846*(i + 0.5)*(j + 0.5) / N);
		return outputData;
	};

} // namespace dsp
} // namespace k52
