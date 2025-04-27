#pragma once
#include "ringheadlist.h"
#include <iostream>
#include <sstream>
using namespace std;


class Monom
{
protected:
    int degree;
    double coeff;
public:
    Monom();
    Monom(int degree, double coeff);
    Monom(const string& s);

    int GetDegree() const;
    double GetCoeff() const;

    bool operator == (const Monom& m) const;
    bool operator != (const Monom& m) const;
    bool operator > (const Monom& m) const;
    bool operator < (const Monom& m) const;
    bool operator >= (const Monom& m) const;
    bool operator <= (const Monom& m) const;

    Monom operator+(const Monom& m);
    Monom operator-(const Monom& m);
    Monom operator*(const Monom& m);

    double operator()(double x, double y, double z) const;

    friend ostream& operator << (ostream& os, const Monom& m)
    {
        if ((m.coeff == 1 || m.coeff == 0) && m.degree == 0)
        {
            os << m.coeff;
            return os;
        }
        if (m.coeff == 0 && m.degree == -1)
        {
            return os;
        }
        if (m.coeff != 1) 
        {
            if (m.coeff == -1 && m.degree != 0)
            {
                os << "-";
            }
            else if (m.coeff != 0)
            {
                os << m.coeff;
            }
        }
        if (m.degree / 100 != 0)
        {
            if (m.degree / 100 == 1)
            {
                os << "x";
            }
            else
            {
                os << "x^" << m.degree / 100;
            }
        }
        if ((m.degree / 10) % 10 != 0)
        {
            if ((m.degree / 10) % 10 == 1)
            {
                os << "y";
            }
            else
            {
                os << "y^" << (m.degree / 10) % 10;
            }
        }
        if (m.degree % 10 != 0)
        {
            if (m.degree % 10 == 1)
            {
                os << "z";
            }
            else
            {
                os << "z^" << m.degree % 10;
            }
        }
        return os;
    }
};