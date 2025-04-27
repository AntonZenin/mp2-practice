/*#include "ringheadlist.h"
#include "tpolynom.h"
#include "headlist.h"
using namespace std;

Monom::Monom(int degree, double coeff)
{
    if (degree < 0 || degree > 999)
    {
        throw "WRONG DEGREE";
    }
    this->degree = degree;
    this->coeff = coeff;
}


Monom::Monom()
{
    degree = -1;
    coeff = 0;
}

Monom::Monom(const string& s) {
    double coeff = 1.0;
    int x_degree = 0, y_degree = 0, z_degree = 0;
    size_t pos = 0;

    
    if (pos < s.size() && s[pos] == '-') {
        coeff = -1.0;
        pos++;
    }

    
    size_t num_end = pos;
    while (num_end < s.size() && (isdigit(s[num_end]) || s[num_end] == '.')) {
        num_end++;
    }

    if (num_end > pos) {
        try {
            coeff *= stod(s.substr(pos, num_end - pos));
        }
        catch (...) {
            throw "Invalid coefficient format";
        }
        pos = num_end;
    }

    
    while (pos < s.size()) {
        if (s[pos] == '*') {
            pos++; 
            continue;
        }

        
        if (s[pos] != 'x' && s[pos] != 'y' && s[pos] != 'z') {
            throw "Invalid variable name (only x, y, z allowed)";
        }

        char var = s[pos];
        pos++;
        int degree = 1; 

        
        if (pos < s.size() && s[pos] == '^') {
            pos++;
            if (pos >= s.size() || !isdigit(s[pos])) {
                throw "Missing degree after ^";
            }

            degree = s[pos] - '0';
            pos++;

            if (degree <= 0 || degree >= 10) {
                throw "Degree must be between 1 and 9";
            }
        }

       
        switch (var) {
        case 'x': x_degree = degree; break;
        case 'y': y_degree = degree; break;
        case 'z': z_degree = degree; break;
        }
    }

    if (coeff == 1.0 && x_degree == 0 && y_degree == 0 && z_degree == 0 && !s.empty()) {
        throw "Invalid monom format";
    }


    this->degree = 100 * x_degree + 10 * y_degree + z_degree;
    this->coeff = coeff;
}

int Monom::GetDegree() const
{
    return degree;
}
double Monom::GetCoeff() const
{
    return coeff;
}

bool Monom::operator == (const Monom& m) const
{
    return (degree == m.degree);
}
bool Monom::operator != (const Monom& m)const
{
    return !(*this == m);
}
bool Monom::operator > (const Monom& m)const
{
    return (degree > m.degree);
}
bool Monom::operator < (const Monom& m)const
{
    return (degree < m.degree);
}
bool Monom::operator >= (const Monom& m)const
{
    return (degree >= m.degree);
}
bool Monom::operator <= (const Monom& m)const
{
    return (degree <= m.degree);
}

Monom Monom:: operator+(const Monom& m)
{
    if (*this != m)
    {
        throw "DIF DEGREES";
    }
    Monom res(degree, coeff + m.coeff);
    return res;
}
Monom Monom:: operator-(const Monom& m)
{
    if (*this != m)
    {
        throw "DIF DEGREES";
    }
    Monom res(degree, coeff - m.coeff);
    return res;
}
Monom Monom::operator*(const Monom& m)
{
    if (((degree) / 100 + (m.degree) / 100) > 9 || (((degree) / 10) % 10 + ((m.degree) / 10) % 10) > 9 || ((degree) % 10 + (m.degree) % 10) > 9)
    {
        throw "WRONG DEGREE";
    }
    Monom res(degree + m.degree, coeff * m.coeff);
    return res;
}

double Monom::operator()(double x, double y, double z)const
{
    double res = 0.0;
    res = coeff * pow(x, (degree / 100)) * pow(y, ((degree / 10) % 10)) * pow(z, (degree % 10));
    return res;
}*/