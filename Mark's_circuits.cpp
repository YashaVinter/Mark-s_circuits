// Mark's_circuits.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#include <iostream>
#include <vector>

#include "input.h"
#include "calculations.h"
#include "boost_calc.h"
#include "output.h"


void Init() {
    std::cout << "Mark's circuits calculation programm" << std::endl;
}
void Finish() {
    std::cout << "Calculations is completed\nAll results saved in C:\\Users\\Public\\results.csv" << std::endl;
}

std::vector<std::string> parse(std::string str, std::string delimiter) {
    std::vector<std::string> vecstr;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string tmp = str.substr(0, pos);
        if (tmp.size() != 0)
            vecstr.push_back(tmp);
        str.erase(0, pos + delimiter.length());
    }
    if (str.size() != 0)
        vecstr.push_back(str);
    return vecstr;
}

std::stringstream InputCSV(std::string path) {
    std::stringstream ss;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::runtime_error er("incorrect path");
        std::cerr << er.what();
        throw er;
    }
    std::string str;
    std::vector<std::string> vecstr;

	while (file)    
    {
        file >> str;
        if (file.eof())
            break;
        auto par = parse(str, ";");
        std::string str_tmp;
        for (size_t i = 0; i < par.size(); i++){
            str_tmp += par[i];
            if (i != par.size() - 1)
                str_tmp += " ";
			if (i == par.size() - 1) 
                str_tmp += "\n";
        }

		for (auto it = std::find(str_tmp.begin(), str_tmp.end(), ','); it != str_tmp.end();
            it = std::find(it, str_tmp.end(), ',')) {
            *it = '.';
        }

        ss << str_tmp;
    } 
    file.close();
    return ss;

    /* start for 0 mode
    * 
        auto par = parse(str, ";");


    ss << str << std::endl;
    //0 mode
    int N;
    file >> N;
    ss << N << std::endl;
    std::vector<StateRecord> table_st;
    for (int i = 0; i < N; i++){
        int st;
        std::string name;
        file >> st;
        file >> name;
    }
    */
}

template<class s>
std::string inp_tst(s& stream) {
    std::string r;
    stream >> r;
    return r;
    
}


//std::string inp_tst(std::istream& stream) {
//    std::string r;
//    stream >> r;
//    return r;
//}


int main()
{
    using namespace std;

    Init();

    //выбор режима ввода: с консоли 0 или файл 1
    std::cout << "Select mode of input data: 0 from console, 1 from CSV file" << std::endl;
    bool inp_mode = 1;
    std::cin >> inp_mode;
    ResultDirectory resultdirectory;
    std::string path_result;

    //Calculations
    vector<vector<double>> result;
    vector<StateRecord> table_st;

    if (!inp_mode)
    {
        resultdirectory = SelectionOfResultDirectory();
        if (resultdirectory == ResultDirectory::choice) {
            std::cin >> path_result;
        }
        //Select mode
        Mode mode = SelectionOfCalculationMode();

        switch (mode)
        {
        case Mode::markovs_circuit:
        {
            //Input Data
            table_st = InputDataTableOfstates();
            int N = table_st.size();
            vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
            int t = InputDataPeriods();
            vector<double> init_prob = InputInitProb(N);

            //Calculations
            vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
            vector<vector<double>> matr_t = TransposeMatrix(matr);
            result = CalculationsOfProbabilities(matr_t, init_prob, t);
            break;
        }
        case Mode::dynamic:
        {
            //Input Data
            table_st = InputDataTableOfstates();
            int N = table_st.size();
            vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
            int t = InputDataPeriods();
            vector<double> init_prob = InputInitProb(N);
            double dt = Input_dt();

            //Calculations
            vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
            matr = IntensityMatrix(matr);
            result = CalculationsOfProbabilities_Dinamic(matr, init_prob, t, dt);
            break;
        }
        case Mode::steady_st:
        {
            //Input Data
            table_st = InputDataTableOfstates();
            int N = table_st.size();
            vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
            //vector<double> init_prob = InputInitProb(N);

            //Calculations
            vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
            matr = IntensityMatrix(matr);
            vector<vector<double>> matr_t = TransposeMatrix(matr);
            vector<vector<double>> matr_coef = MakeMatrCoef(matr_t);
            result = { CalculationsOfProbabilities_StaticState(matr_coef) };
            break;
        }
        default:
            break;
        }
    }
    else
    {
        std::cout << "Please write data path (Example C:/Users/Public/test.csv)" << std::endl;
        std::string path;
        std::cin >> path;
        //path = "C:/Users/Public/test.csv";
		std::stringstream ss(InputCSV(path));

		resultdirectory = SelectionOfResultDirectory(ss);
        if (resultdirectory == ResultDirectory::choice) {
            ss >> path_result;
        }
		Mode mode = SelectionOfCalculationMode(ss);

         switch (mode)
         {
         case Mode::markovs_circuit:
         {
             //Input Data
             table_st = InputDataTableOfstates(ss);
             int N = table_st.size();
             vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities(ss);
             int t = InputDataPeriods(ss);
             vector<double> init_prob = InputInitProb(N, ss);

             //Calculations
             vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
             vector<vector<double>> matr_t = TransposeMatrix(matr);
             result = CalculationsOfProbabilities(matr_t, init_prob, t);
             //toDo smth 
             break;
         }
         case Mode::dynamic:
         {
             //Input Data
             table_st = InputDataTableOfstates(ss);
             int N = table_st.size();
             vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities(ss);
             int t = InputDataPeriods(ss);
             vector<double> init_prob = InputInitProb(N,ss);
             double dt = Input_dt(ss);

             //Calculations
             vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
             matr = IntensityMatrix(matr);
             result = CalculationsOfProbabilities_Dinamic(matr, init_prob, t, dt);
             break;
         }
         case Mode::steady_st:
         {
             //Input Data
             table_st = InputDataTableOfstates(ss);
             int N = table_st.size();
             vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities(ss);
             //vector<double> init_prob = InputInitProb(N);

             //Calculations
             vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
             matr = IntensityMatrix(matr);
             vector<vector<double>> matr_t = TransposeMatrix(matr);
             vector<vector<double>> matr_coef = MakeMatrCoef(matr_t);
             result = { CalculationsOfProbabilities_StaticState(matr_coef) };
             break;
         }
         default:
             break;
         }
    }

    //Output calc
    auto result_t = TransposeMatrix(result);

    
    switch (resultdirectory)
    {
	case ResultDirectory::local :
        path_result = "results.csv";
        break;
    case ResultDirectory::common :
        path_result = "C:/Users/Public/results.csv";
        break;
    case ResultDirectory::choice :
        //selected earlier
        path_result;
        break;
    default:
        break;
    }
	OutputForCSV(result_t, table_st, path_result);
    Finish();
    //std::cin.get();
}

/*
    boost::numeric::ublas::matrix<double> m1 = StdVecVecToBoostMatrix({ {1,2},{3,4} });
    boost::numeric::ublas::matrix<double> m2(2, 2);
    InvertMatrix(m1, m2);

    Init();
    //Input Data
    vector<StateRecord> table_st = InputDataTableOfstates();
    int N = table_st.size();
    vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
    int t = InputDataPeriods();
    vector<double> init_prob = InputInitProb(N); 
    Mode mode = SelectionOfCalculationMode();

    //Calculations
    vector<vector<double>> result;
    


    boost::numeric::ublas::permutation_matrix<std::size_t> pm(m_boost.size1());
    boost::numeric::ublas::matrix<double> inv;
    boost::numeric::ublas::identity_matrix<double> iden(m_boost.size1());
    inv = iden;
    std::cout << m_boost << std::endl;
    boost::numeric::ublas::lu_substitute(m_boost, pm, inv);
    std::cout << inv << std::endl;

    //InvertMatrix(m_boost,inv);
    auto minv_boost = m_boost;

        


    std::ofstream ofs("C:/Users/Public/data1.txt", std::ofstream::out);
    ofs << data.str();
    ofs.close();

    int N1, N2;
    N1 = InputDataPeriods();
    N2 = InputDataPeriods(ss);//ss

    auto& t1 = std::cin;
    auto& t2 = ss;

    std::string testik;
    //testik = ss.str();
    testik = inp_tst(std::cin);
    ss.str("as");
    testik = inp_tst(ss);
    



    //std::cout << "Select directory of output data: 0 this directory, 1 common directory, 2 choice directory yourself" << std::endl;

        //Select mode
    Mode mode = SelectionOfCalculationMode();

    //Calculations
    vector<vector<double>> result;
    vector<StateRecord> table_st;

    switch (mode)
    {
    case Mode::markovs_circuit:
    {
        //Input Data
        table_st = InputDataTableOfstates();
        int N = table_st.size();
        vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
        int t = InputDataPeriods();
        vector<double> init_prob = InputInitProb(N);

        //Calculations
        vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
        vector<vector<double>> matr_t = TransposeMatrix(matr);
        result = CalculationsOfProbabilities(matr_t, init_prob, t);
        break;
    }
    case Mode::dynamic:
    {
        //Input Data
        table_st = InputDataTableOfstates();
        int N = table_st.size();
        vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
        int t = InputDataPeriods();
        vector<double> init_prob = InputInitProb(N);
        double dt = Input_dt();

        //Calculations
        vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
        matr = IntensityMatrix(matr);
        result = CalculationsOfProbabilities_Dinamic(matr, init_prob, t, dt);
        break;
    }
    case Mode::steady_st:
    {
        //Input Data
        table_st = InputDataTableOfstates();
        int N = table_st.size();
        vector<TransitionProbabilityRecord> table_trans_prob = InputDataTableOfTransitionProbabilities();
        //vector<double> init_prob = InputInitProb(N);

        //Calculations
        vector<vector<double>> matr = TransitionMatrix(table_trans_prob, N);
        matr = IntensityMatrix(matr);
        vector<vector<double>> matr_t = TransposeMatrix(matr);
        vector<vector<double>> matr_coef = MakeMatrCoef(matr_t);
        result = { CalculationsOfProbabilities_StaticState(matr_coef) };
        break;
    }
    default:
        break;
    }
*/