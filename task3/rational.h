//
// Created by Игорь on 05.03.2016.
//

#ifndef MYRATIONAL_RATIONAL_H
#define MYRATIONAL_RATIONAL_H


#include <algorithm>

class rational {
public:
    rational(int val);
    rational(int num, int denom);

    int getNum() const;

    int getDenom() const;

    rational operator+(rational const &a) const;

    rational operator-(rational const &a) const;

    rational operator*(rational const &a) const;

    rational operator/(rational const &a) const;

private:
    int numerator, denominator;

};

#endif MYRATIONAL_RATIONAL_H
