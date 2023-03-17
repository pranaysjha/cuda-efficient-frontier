#include "fileio.h"

void readCsv(std::string filename, std::vector<double>& prices)
{
	std::ifstream fin;
	fin.open(filename);
	double price;
	while (fin >> price)
	{
		prices.push_back(price);
	}
	fin.close();
}

void writeCsv(std::string filename)
{

}