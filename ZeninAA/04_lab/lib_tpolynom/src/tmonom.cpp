#include "tpolynom.h"
#include <math.h>
#include "tmonom.h"
#include "ringheadlist.h"
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

Monom::Monom(const string& s) //
{

    string tocken;
    char c;
    double coeff = 1;
    int i = 0, j = 0, k = 0;
    int a = 0;
    for (a; a < s.size(); a++)
    {
        c = s[a];
        if (strchr("-0123456789xyz*^.", c) == nullptr)
        {
            throw "ERROR";
        }
        if (c == '-')
        {
            if (strchr("xyz", s[a + 1]))
            {
                coeff = -1;
                continue;
            }
            tocken += c;
            continue;
        }
        if (strchr("xyz", c))
        {
            if (s[a + 1] == '*' || (a + 1) == s.size())
            {
                switch (c)
                {
                case 'x':
                    i++;
                    break;
                case 'y':
                    j++;
                    break;
                case 'z':
                    k++;
                    break;
                }
                a++;
            }
            continue;
        }
        if (c == '^')
        {
            if ((a + 2 < s.size()) && strchr("0123456789", s[a + 2]))
            {
                throw "WRONG DEGREE";
            }
            switch (s[a - 1])
            {
            case 'x':
                tocken += s[a + 1];
                i = stoi(tocken);
                tocken.clear();
                break;
            case 'y':
                tocken += s[a + 1];
                j = stoi(tocken);
                tocken.clear();
                break;
            case 'z':
                tocken += s[a + 1];
                k = stoi(tocken);
                tocken.clear();
                break;
            }
            a++;
            continue;
        }
        if (c == '*')
        {
            if ((a - 2 > 0) && s[a - 2] == '^')
            {
                continue;
            }
            coeff = stof(tocken);
            tocken.clear();
            continue;
        }
        tocken += c;
    }
    if (!(tocken.empty()))
    {
        coeff = stof(tocken);
    }
    this->degree = 100 * i + 10 * j + k;
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
}