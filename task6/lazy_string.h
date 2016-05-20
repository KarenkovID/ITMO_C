//
// Created by Игорь on 17.05.2016.
//

#ifndef LAZY_STRING_H
#define LAZY_STRING_H

#include <string>
#include <iostream>
#include <memory>
/**
 * The lazy_string class implements Copy-on-Write string
 */
class lazy_string {
private:
    std::shared_ptr<std::string> shp_data_s;
    size_t begin, length;

    lazy_string(std::shared_ptr<std::string> shp_str, size_t begin, size_t length);

    class my_char {
        friend class lazy_string;
    private:

        lazy_string *const ls;
        size_t pos;
    public:
        my_char(lazy_string *const ls, size_t pos);
        my_char &operator=(char ch);
        my_char &operator=(my_char my_ch);
        operator char() const;
    };

public:
    /**
     *  create new lazy_string. Characters like in str
     */
    lazy_string(const std::string &str);

    /**
     * create empty lazy_string
     */
    lazy_string();

    /**
     * @return new lazy_string new_ls.
     * new_ls is substring(characters from begin to begin + length - 1 including) this.
     * @throws @throws  std::out_of_range if begin > size()
     */
    lazy_string substr(size_t begin = 0, size_t length = std::string::npos) const;
    /**
     * @return  std::string containing a copy of the characters of the lazy_string.
     */
    operator std::string() const;
    /**
     * @return character at the position pos (pos = 0..length - 1)
     * @trows std::out_of_range if pos >= length
     */
    char operator[](size_t pos) const;
    my_char operator[](size_t pos);

    /**
     * @return character at the position pos (pos = 0..length - 1)
     * @trows std::out_of_range if pos >= length
     */
    char at(size_t pos) const;
    my_char at(size_t pos) ;

    /*
     * Extracts a string from the input stream is, storing the sequence in lazy_string,
     * overwrite the previous value.
     */
    friend std::istream &operator>>(std::istream &is, lazy_string &ls);

    /**
     * Inserts the sequence of characters that conforms value of str into os.
     */
    friend std::ostream &operator<<(std::ostream &os, lazy_string &ls);

    /**
     * @return length of ls
     */
    size_t get_length();

};

#endif //LAZY_STIRNG_LAZY_STRING_H