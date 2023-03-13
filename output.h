#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "input.h"


std::string DoubleToString(double d);

std::string DotToComma(std::string s);

//void OutputForCSV(std::vector<std::vector<double>> res, std::vector<StateRecord> table_st);
void OutputForCSV(std::vector<std::vector<double>> res, std::vector<StateRecord> table_st, std::string path);