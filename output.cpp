#pragma once

#include "output.h"


std::string DoubleToString(double d) {
    std::stringstream ss;
    ss << std::scientific << d;
    return ss.str();
}

std::string DotToComma(std::string s) {
    std::string str = s;
    for (auto& s1 : str)
        (s1 == '.') ? (s1 = ',') : (0);
    return str;
}

void OutputForCSV(std::vector<std::vector<double>> res, std::vector<StateRecord> table_st, std::string path) {
    std::ofstream ofs(path, std::ofstream::out);
    if (!ofs.is_open()){
        std::runtime_error er("incorrect path");
        std::cerr << er.what();
        throw er;
    }

    for (size_t i = 0; i < res.size(); i++) {
		ofs << table_st[i].name << ';';

        for (size_t j = 0; j < res[0].size(); j++) {
            //ofs << res[i][j];
            ofs << DotToComma(DoubleToString(res[i][j]));

            if (j != res[0].size() - 1)
                ofs << ';';
        }
        if (i != res.size() - 1)
            ofs << '\n';
    }
    ofs.close();
}
