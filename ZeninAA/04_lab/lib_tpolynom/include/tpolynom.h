#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include "tmonom.h"
#include "list.h"
#include "ringheadlist.h"
using namespace std;

class Polinom
{
private:
    void insert(Monom& m);
    Monom last_smaller(const Monom target_key); 

protected:
    string infix;
    RingHeadList<Monom> polinom;
public:
    Polinom() : polinom(), infix() {};
    Polinom(const Polinom& p) : polinom(p.polinom), infix(p.infix) {};
    Polinom(const string& infix);

    Monom getMonom()const;

    bool operator == (const Polinom& p) const;
    bool operator != (const Polinom& p) const;

    Polinom operator+(const Polinom& p);
    Polinom operator-(const Polinom& p);
    Polinom operator*(const Polinom& p);

    Polinom operator+(const Monom& m);
    Polinom operator-(const Monom& m);
    Polinom operator*(const Monom& m);

    Polinom operator+(double a);
    Polinom operator-(double a);
    Polinom operator*(double a);

    const Polinom& operator = (const Polinom& p);

    double operator()(double x, double y, double z)const;

    friend ostream& operator << (ostream& os, Polinom& p)
    {
        p.polinom.reset();
        if (p.polinom.getCurr() == nullptr)
        {
            os << 0;
            return os;
        }
        while (!(p.polinom.is_ended()))
        {
            os << *(p.polinom.getCurr());
            p.polinom.next();
            if (!(p.polinom.is_ended()))
            {
                if (p.polinom.getCurr()->key.GetCoeff() > 0)
                {
                    os << "+";
                }
            }
        }
        return os;
    }
};