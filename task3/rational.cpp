//
// Created by Игорь on 05.03.2016.
//

#include "rational.h"

rational::rational(int val) {
    numerator = val;
    denominator = 1;
}

rational::rational(int num, int denom) {
    int gcd = std::__gcd(num, denom);
    numerator = num / gcd;
    denominator = denom / gcd;
}

int rational::getNum() const {
    return numerator;
}

int rational::getDenom() const {
    return denominator;
}

rational rational::operator+(rational const &a) const {
    int num, denom;
    int gcd = std::__gcd(a.denominator, denominator);
    denom = a.denominator * denominator / gcd;
    num = (a.numerator * (denominator / gcd) +
           numerator * (a.denominator / gcd));
    gcd = std::__gcd(denom, num);
    return rational(num / gcd, denom / gcd);
}

rational rational::operator-(rational const &a) const {
    return ((*this) + rational(-a.numerator, a.denominator));
}

rational rational::operator*(rational const &a) const {
    return rational(this->numerator * a.numerator, this->denominator * a.denominator);
}

rational rational::operator/(rational const &a) const {
    return (*this) * rational(a.denominator, a.numerator);
}