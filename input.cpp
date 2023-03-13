#pragma once

#include "input.h"
//using namespace std;


std::vector<StateRecord> InputDataTableOfstates() {
    // Table of states
    std::cout << "Write number of state (0 to N)" << std::endl;
    int N;
    std::cin >> N;
    std::cout << "Write names of all states (0 new, enter, 1 repair)" << std::endl;
    std::vector<StateRecord> table_st;
    for (int i = 0; i <= N; i++) {
        StateRecord rec;
        std::cin >> rec.number;
        std::cin >> rec.name;
        table_st.push_back(rec);
    }
    return table_st;
}
std::vector<StateRecord> InputDataTableOfstates(std::stringstream& ss) {
    auto& cin = ss;
    // Table of states
    std::cout << "Write number of state (0 to N)" << std::endl;
    int N;
    cin >> N;
    std::cout << "Write names of all states (0 new, enter, 1 repair)" << std::endl;
    std::vector<StateRecord> table_st;
    for (int i = 0; i <= N; i++) {
        StateRecord rec;
        cin >> rec.number;
        cin >> rec.name;
        table_st.push_back(rec);
    }
    return table_st;
}

std::vector<TransitionProbabilityRecord> InputDataTableOfTransitionProbabilities() {
    // Table of transition values
    std::cout << "Write number of connections (1 to M)" << std::endl;
    int M;
    std::cin >> M;
    std::cout << "Write all of transition values (1st state, enter, 2nd state, value) Example: 2 3 0.15" << std::endl;
    std::vector<TransitionProbabilityRecord> table_trans_prob;
    for (int i = 1; i <= M; i++) {
        TransitionProbabilityRecord rec;
        std::cin >> rec.state1;
        std::cin >> rec.state2;
        std::cin >> rec.probability;
        table_trans_prob.push_back(rec);
    }
    return table_trans_prob;
}
std::vector<TransitionProbabilityRecord> InputDataTableOfTransitionProbabilities(std::stringstream& ss) {
    auto& cin = ss;
    // Table of transition values
    std::cout << "Write number of connections (1 to M)" << std::endl;
    int M;
    cin >> M;
    std::cout << "Write all of transition values (1st state, enter, 2nd state, value) Example: 2 3 0.15" << std::endl;
    std::vector<TransitionProbabilityRecord> table_trans_prob;
    for (int i = 1; i <= M; i++) {
        TransitionProbabilityRecord rec;
        cin >> rec.state1;
        cin >> rec.state2;
        cin >> rec.probability;
        table_trans_prob.push_back(rec);
    }
    return table_trans_prob;
}
/*
input.cpp
*/
int InputDataPeriods() {
    std::cout << "Write number of periods calculations (0 to t)" << std::endl;
    int t;
    std::cin >> t;
    return t;
}

int InputDataPeriods(std::stringstream& ss) {
    auto& cin  = ss;
    std::cout << "Write number of periods calculations (0 to t)" << std::endl;
    int t;
    cin >> t;
    return t;
}

double Input_dt() {
    std::cout << "Write time step dt " << std::endl;
    double dt;
    std::cin >> dt;
    return dt;
}
double Input_dt(std::stringstream& ss) {
    auto& cin = ss;
    std::cout << "Write time step dt " << std::endl;
    double dt;
    cin >> dt;
    return dt;
}

std::vector<double> InputInitProb(int dim) {
    std::cout << "Write initial std::vector of probabilities (1 0 0)" << std::endl;
    std::vector<double> ret;
    for (int i = 0; i < dim; i++) {
        double tmp;
        std::cin >> tmp;
        ret.push_back(tmp);
    }
    return ret;
}
std::vector<double> InputInitProb(int dim, std::stringstream& ss) {
    auto& cin = ss;
    std::cout << "Write initial std::vector of probabilities (1 0 0)" << std::endl;
    std::vector<double> ret;
    for (int i = 0; i < dim; i++) {
        double tmp;
        cin >> tmp;
        ret.push_back(tmp);
    }
    return ret;
}

Mode SelectionOfCalculationMode() {
    std::cout << "Select calculation mode (0 - Markov's circuit, 1 - dynamic process, 2 - static state)" << std::endl;
    int m;
    std::cin >> m;
    switch (m)
    {
	case 0:
        return Mode::markovs_circuit;
        break;
	case 1:
        return Mode::dynamic;
        break;
    case 2:
        return Mode::steady_st;
        break;
    default:
        std::runtime_error er("undefined mode");
        std::cerr << er.what();
        throw er;
        break;
    }
}
Mode SelectionOfCalculationMode(std::stringstream& ss) {
    auto& cin = ss;
    std::cout << "Select calculation mode (0 - Markov's circuit, 1 - dynamic process, 2 - static state)" << std::endl;
    int m;
    cin >> m;
    switch (m)
    {
    case 0:
        return Mode::markovs_circuit;
        break;
    case 1:
        return Mode::dynamic;
        break;
    case 2:
        return Mode::steady_st;
        break;
    default:
        std::runtime_error er("undefined mode");
        std::cerr << er.what();
        throw er;
        break;
    }
}

ResultDirectory SelectionOfResultDirectory() {
    std::cout << "Select directory of output data: 0 this directory, 1 common directory, 2 choice directory yourself" << std::endl;
    int m;
    std::cin >> m;
    switch (m)
    {
    case 0:
        return ResultDirectory::local;
        break;
    case 1:
        return ResultDirectory::common;
        break;
    case 2:
        return ResultDirectory::choice;
        break;
    default:
        std::runtime_error er("undefined mode");
        std::cerr << er.what();
        throw er;
        break;
    }
}
ResultDirectory SelectionOfResultDirectory(std::stringstream& ss) {
    auto& cin = ss;
    std::cout << "Select directory of output data: 0 this directory, 1 common directory, 2 choice directory yourself" << std::endl;
    int m;
    cin >> m;
    switch (m)
    {
    case 0:
        return ResultDirectory::local;
        break;
    case 1:
        return ResultDirectory::common;
        break;
    case 2:
        return ResultDirectory::choice;
        break;
    default:
        std::runtime_error er("undefined mode");
        std::cerr << er.what();
        throw er;
        break;
    }
}

//std::stringstream& operator>> (std::stringstream& is, std::string& in);
//std::stringstream& operator>> (std::stringstream& is, int& in)
//{
//    std::string s;
//    is >> s;
//    in = std::stoi(s);
//    //is >> in;
//    return is;
//}
//std::stringstream& operator>> (std::stringstream& is, std::string& in)
//{   
//    in = is.std::stringstream::str();
//    //is >> in;
//    return is;
//}