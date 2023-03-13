#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

struct StateRecord
{
    int number;
    std::string name;
};
struct TransitionProbabilityRecord
{
    int state1;
    int state2;
    double probability;
};
// calculation mode (0 - Markov's circuit, 1 - dynamic process, 2 - static state)
enum class Mode
{
    markovs_circuit,
    dynamic,
    steady_st
};
enum class ResultDirectory
{
    local,
    common,
    choice
};

std::vector<StateRecord> InputDataTableOfstates();
std::vector<StateRecord> InputDataTableOfstates(std::stringstream& ss);
std::vector<TransitionProbabilityRecord> InputDataTableOfTransitionProbabilities();
std::vector<TransitionProbabilityRecord> InputDataTableOfTransitionProbabilities(std::stringstream& ss);
int InputDataPeriods();
int InputDataPeriods(std::stringstream& ss);
double Input_dt();
double Input_dt(std::stringstream& ss);
std::vector<double> InputInitProb(int dim);
std::vector<double> InputInitProb(int dim, std::stringstream& ss);
Mode SelectionOfCalculationMode();
Mode SelectionOfCalculationMode(std::stringstream& ss);
ResultDirectory SelectionOfResultDirectory();
ResultDirectory SelectionOfResultDirectory(std::stringstream& ss);