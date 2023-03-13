#pragma once

#include <iostream>
#include <vector>
#include <boost/numeric/ublas/triangular.hpp>
//#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>

boost::numeric::ublas::vector<double>  StdVecToBoostVec(const std::vector<double>& stdvec);

boost::numeric::ublas::matrix<double>  StdVecVecToBoostMatrix(const std::vector<std::vector<double>>& stdvec);

bool InvertMatrix(const boost::numeric::ublas::matrix<double>& input, boost::numeric::ublas::matrix<double>& inverse);

std::vector<double> CalculationsOfProbabilities_StaticState(std::vector<std::vector<double>> m);

boost::numeric::ublas::matrix<double> func();