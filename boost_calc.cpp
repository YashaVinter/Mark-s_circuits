#pragma once
#include <iostream>
#include <vector>

#include "boost_calc.h"


boost::numeric::ublas::vector<double>  StdVecToBoostVec(const std::vector<double>& stdvec) {
    //boost::numeric::ublas::vector<double> boostvec(stdvec.size());
    //std::copy(stdvec.begin(), stdvec.end(), boostvec.begin());
    //return boostvec;
    boost::numeric::ublas::vector<double> boostvec(stdvec.size());
    for (int i = 0; i < stdvec.size(); ++i) {
        boostvec[i] = stdvec.at(i);
    }
    return boostvec;
}

boost::numeric::ublas::matrix<double>  StdVecVecToBoostMatrix(const std::vector<std::vector<double>>& stdvec) {
    boost::numeric::ublas::matrix<double> boostvec(stdvec.size(), stdvec.size());
    for (int i = 0; i < stdvec.size(); ++i) {
        for (int j = 0; j < stdvec.size(); ++j) {
            boostvec(i, j) = stdvec.at(i).at(j);
        }
    }
    return boostvec;
}

bool InvertMatrix(const boost::numeric::ublas::matrix<double>& input, boost::numeric::ublas::matrix<double>& inverse ){
    using namespace boost::numeric::ublas;
    typedef  boost::numeric::ublas::permutation_matrix<std::size_t> pmatrix;
    // create a working copy of the input
    matrix<double> A(input);
    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());

    // perform LU-factorization
    int res = lu_factorize(A, pm);
    if (res != 0) return false;

    // create identity matrix of "inverse"
    inverse.assign(boost::numeric::ublas::identity_matrix<double>(A.size1()));

    // backsubstitute to get the inverse
    lu_substitute(A, pm, inverse);

    return true;
}

//for 2 mode
std::vector<double> CalculationsOfProbabilities_StaticState(std::vector<std::vector<double>> m) {

    std::vector<double> B(m.size(), 0);
    B[B.size() - 1] = 1;

    auto m_boost = StdVecVecToBoostMatrix(m);
    auto B_boost = StdVecToBoostVec(B);
    //Calc
    auto m_boost_inv = m_boost;
    InvertMatrix(m_boost, m_boost_inv);
    boost::numeric::ublas::vector<double> res_boost = prod(m_boost_inv, B_boost);

    std::vector<double> res;
    for (size_t i = 0; i < res_boost.size(); i++) {
        res.push_back(res_boost(i));
    }
    return res;
}

boost::numeric::ublas::matrix<double> func() {
    boost::numeric::ublas::matrix<double> m(2, 2);
    return m;
}

