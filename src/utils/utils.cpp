#include <iostream>
#include <string>

#include "utils/utils.hpp"

using namespace std;

bool utils::extractString(string& str) {
    if (str.length() < 3){
        cerr << "error: Name insufficient length" << endl;
        return false;
    }

    if (str[0] == '\'' && str[str.length()-1] == '\'') {
        str = str.substr(1, str.length()-2);
        return true;    
    } else {
        cerr << "error: Name must be passed through single quotes" << endl;
        return false;
    }
}