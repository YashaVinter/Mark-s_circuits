#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "input.h"
#include "calculations.h"
using namespace std;

std::vector<double> OpWithVectors(std::vector<double> v1, std::vector<double> v2, char ch) {
    for (size_t i = 0; i < v1.size(); i++) {
        if (ch == '+')
            v1[i] += v2[i];
        if (ch == '-')
            v1[i] -= v2[i];
        if (ch == '*')
            v1[i] *= v2[i];
        if (ch == '/')
            v1[i] /= v2[i];
    }
    return v1;
}

//for 0 mode
vector<vector<double>> TransitionMatrix(vector<TransitionProbabilityRecord> table_trans_prob, int dim) {
    // making transition matrix from init table
    vector<vector<double>> matrix(dim);
    for (auto& m : matrix) {
        m.resize(dim);
    }
    for (size_t k = 0; k < table_trans_prob.size(); k++) {
        TransitionProbabilityRecord rec = table_trans_prob.at(k);
        int i = rec.state1;
        int j = rec.state2;
        matrix[i][j] = rec.probability;
    }
    return matrix;
}

//for 1,2 mode
vector<vector<double>> IntensityMatrix(vector<vector<double>> trans_m) {
    vector<vector<double>> inten_matr = trans_m;
    // neeed to add diag elements
    for (size_t i = 0; i < trans_m.size(); i++) {
        double diag_tmp = 0;
        for (size_t j = 0; j < trans_m.at(0).size(); j++) {
            if (i != j)
                diag_tmp += trans_m.at(i).at(j);
        }
        inten_matr[i][i] = -diag_tmp;
    }
    return inten_matr;
}

vector<vector<double>> CalculationsOfProbabilities_Dinamic(
    vector<vector<double>> matr, vector<double> init_prob, int t, double dt) {

    vector<vector<double>> result{ init_prob };
    //preparing matr
    vector<double> vecnull(matr.size(), 0);
    matr.pop_back();
    matr.push_back(vecnull);
    vector<vector<double>> matr_t = TransposeMatrix(matr);
    //L_rash*P(t)
    for (size_t i = 0; i < matr_t.size(); i++) {
        for (size_t j = 0; j < matr_t.at(0).size(); j++) {
            matr_t[i][j] *= dt;
        }
    }

    for (int i = 0; i < t; i++) {
        vector<double> dPi = (MulMatrVec(matr_t, result[i]));
        vector<double>res_i = OpWithVectors(result[i], dPi, '+');
        /*double sum_prob_without_last = 0;
        for (int i = 0; i < res_i.size() - 1; ++i) {
            sum_prob_without_last += res_i[i];
        }
        res_i[res_i.size() - 1] = 1 - sum_prob_without_last;*/
        result.push_back(res_i);
    }
    return result;
}

vector<vector<double>> TransposeMatrix(vector<vector<double>> m) {
    vector<vector<double>> m_t(m[0].size());
    for (auto& m1 : m_t) {
        m1.resize(m.size());
    }
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m[0].size(); j++)
            m_t[j][i] = m[i][j];
    return m_t;
}
vector<double> MulMatrVec(vector<vector<double>> m, vector<double> v) {
    vector<double> res;
    for (size_t i = 0; i < m[0].size(); i++) {
        double tmp = 0;
        for (size_t j = 0; j < m[0].size(); j++) {
            tmp += m[i][j] * v[j];
        }
        res.push_back(tmp);
    }
    return res;
}


//0 mode
vector<vector<double>> CalculationsOfProbabilities(vector<vector<double>> matr_t, vector<double> init_prob, int t) {
    vector<vector<double>> result{ init_prob };
    for (int i = 0; i < t; i++) {
        result.push_back(MulMatrVec(matr_t, result[i]));
    }
    return result;
}

vector<vector<double>> MakeMatrCoef(vector<vector<double>> m) {
    vector<double> identvec(m.size(), 1);
    m[m.size() - 1] = identvec;
    return m;
}


