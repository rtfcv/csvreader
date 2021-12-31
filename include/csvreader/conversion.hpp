#include <string>
#include <iostream>
#include <boost/type_index.hpp>

namespace CR {
    /**
     * convert from one type to the other
     * Type2 output = convert<Type1,Type2>(Type1 input);
     */
    template <typename T1, typename T2>
    T2 convert(T1 input){
        T2 out;
        std::cout << "conversion from:\n" 
            << boost::typeindex::type_id_runtime(input)
            << "\nto:\n"
            << boost::typeindex::type_id_runtime(out)
            << "\nis not implemented yet\n"
            << "but you can implement that yourself like:\n"
            << "    template <>\n"
            << "    [type of output] __CR::convert([type of input] input){\n"
            << "            return [actual conversion](input);\n"
            << "    }\n"
            <<std::endl;
        abort();
        return out;
    }


    // string -> string
    template <>
    inline std::string convert(std::string input){
        return input;
    }
    // string -> float
    template <>
    inline float convert(std::string input){
        return std::stof(input);
    }
    // string -> double
    template <>
    inline double convert(std::string input){
        return std::stod(input);
    }
    // string -> int
    template <>
    inline int convert(std::string input){
        return std::stoi(input);
    }


    // float -> string
    template <>
    inline std::string convert(float input){
        return std::to_string(input);
    }
    // float -> float
    template <>
    inline float convert(float input){
        return float(input);
    }
    // float -> double
    template <>
    inline double convert(float input){
        return double(input);
    }
    // float -> int
    template <>
    inline int convert(float input){
        return int(input);
    }


    // double -> string
    template <>
    inline std::string convert(double input){
        return std::to_string(input);
    }
    // double -> float
    template <>
    inline float convert(double input){
        return float(input);
    }
    // double -> double
    template <>
    inline double convert(double input){
        return double(input);
    }
    // double -> int
    template <>
    inline int convert(double input){
        return int(input);
    }


    // int -> string
    template <>
    inline std::string convert(int input){
        return std::to_string(input);
    }
    // int -> float
    template <>
    inline float convert(int input){
        return float(input);
    }
    // int -> int
    template <>
    inline double convert(int input){
        return double(input);
    }
    // int -> int
    template <>
    inline int convert(int input){
        return int(input);
    }
}
