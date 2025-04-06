#pragma once

#include <iostream>
#include <sstream>
using namespace std;
class TMonom {
public:
    double coeff_;
    int degree_;

    TMonom();
    TMonom(double coeff, int degree);
    bool operator<(const TMonom&) const;
    bool operator<=(const TMonom&) const;
    bool operator>(const TMonom&) const;
    bool operator>=(const TMonom&) const;
    bool operator==(const TMonom&) const;
    bool operator!=(const TMonom&) const;

    friend ostream& operator<< (ostream& out, const TMonom& m) {
        out << m.coeff_ << "  " << m.degree_ << endl;
        return out;
    }
};