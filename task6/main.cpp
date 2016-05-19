#include <iostream>
#include <string>
#include "lazy_string.h"
using namespace std;

int main() {
    lazy_string ls("lalka");
    cout << ls << endl;
    lazy_string ls1 = ls.substr(0, 2);
    cout << ls1 << endl;

    cin >> ls1;
    ls1 = ls1.substr(2, 2);
    cout << ls1;
    return 0;
}