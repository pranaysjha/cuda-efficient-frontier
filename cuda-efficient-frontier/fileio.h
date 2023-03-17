#pragma once

#include <string>
#include <vector>
#include <valarray>
#include <fstream>

void readCsv(std::string filename, std::vector<double> &prices);

void writeCsv(std::string filename);
