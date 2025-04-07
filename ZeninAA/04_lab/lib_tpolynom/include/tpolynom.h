#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include "tmonom.h"
#include "list.h"
#include "ringheadlist.h"
using namespace std;

class TPolynom {
protected:
    string name;
    headlist<TMonom> monoms;

    void smash_pol(const string& name);                     
    bool check(const string& name);                         
    void InsertToSort(const TMonom& monom);                 
public:
    TPolynom() : monoms() {}
    TPolynom(const string& name);
    TPolynom(const headlist<TMonom>& l);
    TPolynom(const TPolynom& p);
    ~TPolynom() = default;

    TPolynom operator-() const;
    TPolynom operator+(const TPolynom& p);
    TPolynom operator-(const TPolynom& p);
    TPolynom operator*(const TPolynom& p);
    bool operator==(const TPolynom& p) const;

    string TPolynom::ToString() const;              

    double operator()(double x, double y, double z) const;
    TPolynom dx() const;
    TPolynom dy() const;
    TPolynom dz() const;

    const TPolynom& operator=(const TPolynom& p);

    friend ostream& operator<< (ostream& out, TPolynom& pol) {
        if (pol.monoms.IsEmpty()) {
            out << "Empty!" << "\n";
            return out;
        }
        pol.monoms.Reset();
        while (!pol.monoms.IsEnded()) {
            out << pol.monoms.GetCurr()->data;
            pol.monoms.Next();
        }
        return out;
    }
};