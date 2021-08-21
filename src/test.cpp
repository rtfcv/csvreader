#include <csvreader/csvreader.hpp>

#include <csvreader/vector_op.hpp>
#include <csvreader/map_op.hpp>

#include <string>
#include <vector>
#include <map>

#include <csvreader/readcsv.h>

#define for_in(i, it) for(auto i=it.begin(); i!=it.end(); i++)


/**
 * aditional conversion function required for
 * string -> long long
 */
template <>
long long __CR::convert(float input){
        return (long long)input;
}


int main(){
    std::string _nl = "\n";

    //playing around
    CsvReader<float> rdr = CsvReader<float>("testdata/test.csv", true);
    rdr.set_index("col1");

    std::cout << rdr << std::endl;

    //
    auto m = rdr.col_map<long long>("col2");
    std::cout << m << std::endl;

    return 0;
}
