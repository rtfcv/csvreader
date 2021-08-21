#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


template <typename __TYPE>
inline std::vector<std::vector<__TYPE>> read_csv(std::string fname, int skip_rows, int skip_cols){
    std::fstream fin;
    fin.open(fname, std::ios::in);

    // string for a line, string for each element of csv
    // will later use them in the inner loop
    std::string line, word;
    std::stringstream element_ss;
    __TYPE element;

    // vector where answer goes
    std::vector<std::vector<__TYPE>> matrix;

    //index to check which row and column we are on
    int irow=0;
    int jcol=0;

    while (std::getline(fin, line)) {
        //check if the rows are to be skipped
        if (irow < skip_rows){irow++;continue;}

        std::vector<__TYPE> row;
        std::stringstream rawline(line);

        // in case the csv has cr+lf line ending
        std::getline(rawline, line, '\r');
        std::stringstream s(line);

        jcol=0;// reset the counter

        // pack each element of a line into row vector
        while (std::getline(s, word, ',')) {
            // check if the cols are to be skipped
            if (jcol < skip_cols){jcol++;continue;}
            // convert the string `word' into a stringstream
            element_ss = std::stringstream(word);
            // to later convert into the template `__TYPE' using operator >>
            element_ss >> element;
            row.push_back(element);
        }

        // add the row vector to the matrix
        matrix.push_back(row);
    }

    return matrix;
}


template <typename __TYPE>
inline std::vector<std::vector<__TYPE>> read_csv(std::string fname){
    return read_csv<__TYPE>(fname, 0, 0);
}
