#include "lazy_string.h"

lazy_string::lazy_string(const std::string& str) :
        shp_data_s(std::make_shared<std::string>(str)),
        length(str.length()),
        begin(0u) {}

lazy_string::lazy_string(std::shared_ptr<std::string> shp_str, size_t begin, size_t length):
        shp_data_s(shp_str),
        begin(begin),
        length(length){}

lazy_string::lazy_string():
        shp_data_s(std::make_shared<std::string>(std::string())),
        begin(0),
        length(0){}
lazy_string lazy_string::substr(unsigned begin, unsigned length) const{
    if (begin >= this->length) {
        throw std::out_of_range("lazy_string");
    }
    length = std::min(length, this->length - begin);
    return lazy_string(shp_data_s, this->begin + begin, length);
}

std::istream &operator>>(std::istream &is, lazy_string &ls) {
    std::shared_ptr<std::string> shp_str = std::make_shared<std::string>();
    is >> *shp_str;
    ls.shp_data_s = shp_str;
    ls.begin = 0;
    ls.length = ls.shp_data_s->length();
    return  is;

}
std::ostream &operator<<(std::ostream &os, lazy_string &ls) {
    os << (std::string)ls;
    return os;
}

char lazy_string::at(unsigned pos) const{
    if (pos >= length) {
        throw std::out_of_range("lazy_string");
    }
    return shp_data_s->at(begin + pos);
}

lazy_string::my_char lazy_string::at(unsigned pos) {
    if (pos >= length) {
        throw std::out_of_range("lazy_string");
    }
    return my_char(this, begin + pos);
}

char lazy_string::operator[](unsigned pos) const{
    return at(pos);
}

lazy_string::my_char lazy_string::operator[](unsigned pos){
    return at(pos);
}

lazy_string::operator std::string() const{
    return shp_data_s->substr(begin, length);
}
unsigned lazy_string::get_length() {
    return length;
}

lazy_string::my_char::my_char(lazy_string *const ls, unsigned pos): ls(ls), pos(pos){}

lazy_string::my_char &lazy_string::my_char::operator=(char ch) {
    if (ls->shp_data_s.use_count() > 1) {
        std::string str = ls->shp_data_s->substr(ls->begin, ls->length);
        ls->shp_data_s = std::make_shared<std::string>(str);
    }
    ls->shp_data_s->at(pos) = ch;
    return *this;
}
lazy_string::my_char &lazy_string::my_char::operator=(lazy_string::my_char my_ch) {
    char ch = my_ch;
    return *this = ch;
}

lazy_string::my_char::operator char() const {
    return ls->shp_data_s->at(pos);
}