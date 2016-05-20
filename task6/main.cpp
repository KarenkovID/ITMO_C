#include <iostream>
#include <string>
#include "lazy_string.h"
using namespace std;

int main() {
    const string str = "sdfgsdfg";
    lazy_string ls(str);
    cout << ls[0] << endl;
    lazy_string ls1 = ls.substr(0, 2);
    cout << ls1 << endl;

    return 0;
}