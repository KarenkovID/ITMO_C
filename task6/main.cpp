#include <iostream>
#include <string>
#include "lazy_string.h"
using namespace std;

int main() {
    lazy_string ls("kek\n");
    cout << ls << endl;
    lazy_string s = ls.substr(1);

    ls[0] = ls[2] = 'l';
    cout << ls;
    return 0;
}