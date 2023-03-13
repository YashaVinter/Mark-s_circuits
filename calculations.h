#pragma once

#include <vector>

std::vector<double> OpWithVectors(std::vector<double> v1, std::vector<double> v2, char ch);

std::vector<std::vector<double>> TransitionMatrix(
	std::vector<TransitionProbabilityRecord> table_trans_prob, int dim);

std::vector<std::vector<double>> IntensityMatrix(std::vector<std::vector<double>> trans_m);

std::vector<std::vector<double>> CalculationsOfProbabilities_Dinamic(
	std::vector<std::vector<double>> matr, std::vector<double> init_prob, int t, double dt);

std::vector<std::vector<double>> TransposeMatrix(std::vector<std::vector<double>> m);

std::vector<double> MulMatrVec(std::vector<std::vector<double>> m, std::vector<double> v);

std::vector<std::vector<double>> CalculationsOfProbabilities(
	std::vector<std::vector<double>> matr_t, std::vector<double> init_prob, int t);

std::vector<std::vector<double>> MakeMatrCoef(std::vector<std::vector<double>> m);

