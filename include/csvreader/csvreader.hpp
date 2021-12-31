#pragma once

#include <csvreader/conversion.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>



template <typename CR_TYPE>
class CsvReader{
private:
    std::vector<std::vector<CR_TYPE>> dataMatrix;
    std::vector<std::string> CR_header;
    std::vector<CR_TYPE> CR_index;
    int num_colskip;


    /**
     * actual part where initialization is done
     * the constructors are just wrappers for this
     * this is also where all the parsing of csv is done
     */
    void initialize(std::string fname, int skip_col, bool header){
        num_colskip=skip_col;
        CR_header.clear();
        dataMatrix.clear();

        std::fstream fin;
        fin.open(fname, std::ios::in);
        if(!fin.is_open()){
            std::cout<<"FAILED to open file \'"<<fname<<"\'"<<std::endl;
            abort();
        }

        //string for a line, string for each element of csv
        std::string line, word;
        // will later use them in the inner loop
        CR_TYPE element;

        // read header if told
        if(header){
            std::getline(fin, line);
            std::vector<CR_TYPE> row;

            //create string stream for splitting the line
            std::stringstream rawline(line);
            //in case the csv has cr+lf line ending
            std::getline(rawline, line, '\r');
            //now the actual stringstream we are going to use
            std::stringstream s(line);

            int oncol=1;
            while (std::getline(s, word, ',')) {
                if(oncol <= num_colskip){oncol++;continue;}
                CR_header.push_back(word);
            }
        }

        // read everything that is not a header
        while (std::getline(fin, line)) {
            std::vector<CR_TYPE> row;
            std::stringstream s(line);

            // parse the row
            int oncol=1;
            while (std::getline(s, word, ',')) {
                if(oncol <= num_colskip){oncol++;continue;}
                // convert the string `word' into a stringstream
                // to convert into the template `CR_TYPE' using operator >>
                std::stringstream(word) >> element;
                row.push_back(element);
            }
            dataMatrix.push_back(row);
        }
    }




public:
    //constructors
    CsvReader(std::string fname){
        initialize(fname,0,false);
    }
    CsvReader(std::string fname,bool header){
        initialize(fname,0,header);
    }
    CsvReader(std::string fname, int skip_col){
        initialize(fname,skip_col,false);
    }
    CsvReader(std::string fname, int skip_col, bool header){
        initialize(fname,skip_col,false);
    }


    /**
     * returns the internal data matrix
     */
    std::vector<std::vector<CR_TYPE>> get_data(){
        return dataMatrix;
    }


    /**
     * set which column is used as index
     */
    int set_index(std::string col_name){
        CR_index = col(col_name);
        return 0;
    }


    /**
     * returns an vector of columns
     */
    std::vector<CR_TYPE> col(std::string key){
        std::vector<CR_TYPE> slice = {};
        int l=CR_header.size();
        int the_index=-1;

        for(int i=0; i<l; i++){
            if(CR_header[i]==key){
                the_index=i;
                break;
            }
        }

        if(the_index == -1){
            std::cout<<"the Key not in the header..."<<std::endl;
            return {};
        }

        l=dataMatrix.size();
        for(int i=0; i<l; i++){
            slice.push_back(dataMatrix[i][the_index]);
        }

        return slice;
    }


    /**
     * returns an map of columns
     */
    std::map<CR_TYPE,CR_TYPE> col_map(std::string key){
        std::map<CR_TYPE,CR_TYPE> slice = {};
        int l=CR_header.size();
        int the_index=-1;

        //search which column the `key' specify
        for(int i=0; i<l; i++){
            if(CR_header[i]==key){
                the_index=i;
                break;
            }
        }

        if(the_index == -1){
            std::cout<<"the Key not in the header..."<<std::endl;
            return {};
        }

        l=dataMatrix.size();
        for(int i=0; i<l; i++){
            slice[CR_index[i]] = dataMatrix[i][the_index];
        }

        return slice;
    }


    /**
     * returns an map of columns of a particular type
     */
    template <typename CR_TYPE_col_output>
    std::map<CR_TYPE,CR_TYPE_col_output> col_map(std::string key){
        std::map<CR_TYPE,CR_TYPE_col_output> slice = {};
        int l=CR_header.size();
        int the_index=-1;

        //search which column the `key' specify
        for(int i=0; i<l; i++){
            if(CR_header[i]==key){
                the_index=i;
                break;
            }
        }

        if(the_index == -1){
            std::cout<<"the Key not in the header..."<<std::endl;
            return {};
        }

        l=dataMatrix.size();
        for(int i=0; i<l; i++){
            slice[CR_index[i]] = CR::convert<CR_TYPE, CR_TYPE_col_output>(dataMatrix[i][the_index]);
            //std::stringstream(std::to_string(dataMatrix[i][the_index])) >> slice[CR_index[i]];
        }

        return slice;
    }


    /**
     * returns an array of columns
     */
    std::vector<CR_TYPE> row_by_index(int i){
        return dataMatrix[i];
    }


    /**
     * get a element by col name and index_string
     */
    CR_TYPE loc(std::string col_name, CR_TYPE index){
        //check if index is even set

        //then
        int l=CR_index.size();
        int the_index=-1;

        //look for the internal index of readable index
        for(int i=0; i<l; i++){
            if(CR_index[i]==index){
                the_index=i;
                break;
            }
        }

        if(the_index == -1){
            std::cout<<"the index given was not in the index column..."<<std::endl;
            abort();
        }

        return col(col_name)[the_index];
    }


    /**
     * returns an array of headers
     */
    std::vector<std::string> header(){
        return CR_header;
    }

    /**
     * returns an vector of index column
     */
    std::vector<CR_TYPE> index(){
        return CR_index;
    }

    /**
     * returns an vector of index column
     */
    std::vector<size_t> size(){
        return {dataMatrix.size(), dataMatrix.begin()->size()};
    }

    CR_TYPE operator () (std::string col, CR_TYPE index){
        return loc(col, index);
    }

    std::vector<CR_TYPE> operator [](int i){
        return dataMatrix[i];
    }
};



/**
 * define operator << for use in outputstream
 */
template <typename CR_TYPE>
inline std::ostream& operator << (std::ostream& ostr,  CsvReader<CR_TYPE>& cr) {
    auto CR_header = cr.header();
    auto CR_index = cr.header();

    if (! CR_header.empty()) {
        ostr << CR_header.front();
        for (auto itr = ++CR_header.begin(); itr !=CR_header.end(); itr++){
            ostr << "\t" << *itr;
        }
        ostr << "\n";
    }

    // what if we do not have headers
    // this is not robust for now
    int ncols = CR_header.size();
    int nrows = cr.col(CR_header[0]).size();

    for (int i=0; i<nrows; i++){
        std::string delim = "";
        auto __row = cr.row_by_index(i);

        for (int j=0; j<ncols; j++) {
            ostr << delim << __row[j];
            delim = "\t";
        }
        ostr << "\n";
    }
    return ostr;
}
