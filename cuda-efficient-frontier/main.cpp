#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>
#include <algorithm>

#include "cublas_v2.h"

#include "fileio.h"

double expected_val(std::vector<double> nums)
{
	double sum = 0;
	for (double n : nums) sum += n;
	return sum / nums.size();
}

int main(int argc, char* argv[])
{
	// Read returns data and compute expected returns
	int num_assets = argc - 1;
	std::vector<std::vector<double>> vec_returns(num_assets);
	std::vector<std::string> symbols(num_assets);
	std::vector<double> expected_returns(num_assets);
	char delim = '.';
	for (int i = 0; i < num_assets; i++) {
		std::string filename = argv[i + 1];
		readCsv(filename, vec_returns[i]);
		symbols[i] = filename.substr(0, filename.find(delim));
		expected_returns[i] = expected_val(vec_returns[i]);
		std::cout << symbols[i] << ", " << expected_returns[i] << std::endl;
	}

	// Convert vectors to arrays
	size_t days = vec_returns[0].size();
	double** arr_X = new double*[num_assets];
	for (int i = 0; i < num_assets; i++) {
		arr_X[i] = new double[days];
		double curr_exp_ret = expected_returns[i];
		// Subtract expected return from each element (x - x-bar)
		std::for_each(vec_returns[i].begin(), vec_returns[i].end(), [=](double x)
		{
			return x - curr_exp_ret;
		});
		std::copy(vec_returns[i].begin(), vec_returns[i].end(), arr_X[i]);
	}

	// Flatten arr_X
	
	// Compute (X * X^T)/(n - 1) to get covariance matrix with cuBLAS

	// Generate random vectors of asset weights for 10000 trials with cuRAND

	// Compute expected portfolio returns and volatility in CUDA kernel and with cuBLAS
	// sqrt(W * V * W^T)

	// Write results to CSV (weights, expected portfolio return, volatility)

}