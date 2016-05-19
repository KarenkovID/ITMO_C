//
// Created by Игорь on 17.05.2016.
//

#ifndef LAZY_STRING_H
#define LAZY_STRING_H

#include <string>
#include <iostream>
#include <memory>
class lazy_string {
public:
    lazy_string(const std::string& str);
    lazy_string();
    lazy_string substr(unsigned begin, unsigned length);
    operator std::string();
    char operator[](unsigned pos);
    char at(unsigned pos);
    friend std::istream &operator>>(std::istream &is, lazy_string &ls);
    friend std::ostream &operator<<(std::ostream &os, lazy_string &ls);
private:
    std::shared_ptr<std::string> shp_data_s;
    size_t begin, length;
    lazy_string(std::shared_ptr<std::string> shp_str, size_t begin, size_t length);
};
#endif //LAZY_STIRNG_LAZY_STRING_H
