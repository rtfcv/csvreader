#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template <typename T>
inline std::ostream& operator << (std::ostream& ostr, const std::vector<std::vector<T>>& v) {
    if (v.empty()) {
        ostr << "{ }";
        return ostr;
    }

    ostr << "{" << v.front();
    for (auto itr = ++v.begin(); itr != v.end(); itr++) {
        ostr << ",\n " << *itr;
    }
    ostr << "}";
    return ostr;
}


template <typename T>
inline std::ostream& operator << (std::ostream& ostr, const std::vector<T>& v) {
    if (v.empty()) {
        ostr << "{ }";
        return ostr;
    }

    ostr << "{" << v.front();
    for (auto itr = ++v.begin(); itr != v.end(); itr++) {
        ostr << ", " << *itr;
    }
    ostr << "}";
    return ostr;
}

template <typename T>
inline std::vector<T> operator-(std::vector<T> &output, const std::vector<std::string> &input) {
    output.clear();
    std::stringstream item;
    std::string word;
    for (auto itr=input.begin(); itr!=input.end(); itr++){
        T element;
        std::stringstream(*itr) >> element;
        output.push_back(element);
    }
    return output;
}


/**
 * convert types of vector
 */
template <typename T>
inline std::vector<std::string> operator << (std::vector<std::string> &lhs, const std::vector<T> &rhs) {
    lhs.clear();
    for (auto itr=rhs.begin(); itr!=rhs.end(); itr++){
        lhs.push_back(std::to_string(*itr));
    }
    return lhs;
}
