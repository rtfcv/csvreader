#include <iostream>
#include <string>
#include <map>


template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& ostr, std::map<T1,T2>& m) {
    if (m.empty()) {
        ostr << "{}";
        return ostr;
    }

    for (auto itr = m.begin(); itr != m.end(); itr++) {
        ostr << itr->first << ": ";
        ostr << itr->second << "\n";
    }
    return ostr;
}
