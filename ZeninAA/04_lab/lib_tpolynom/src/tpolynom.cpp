#include "tpolynom.h"
#include <math.h>

Monom::Monom()
{
    degree = -1;
    coeff = 0;
}
Monom::Monom(int degree, double coeff)
{
    if (degree < 0 || degree > 999)
    {
        throw "degree is out of range!";
    }
    this->degree = degree;
    this->coeff = coeff;
}
Monom::Monom(const string& s)
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
            throw "incorrect input!";
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
                throw "Degrees should be less than 10 and greater than 0!";
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
        throw "monoms have to be same degree to sum";
    }
    Monom res(degree, coeff + m.coeff);
    return res;
}
Monom Monom:: operator-(const Monom& m)
{
    if (*this != m)
    {
        throw "monoms have to be same degree to sub";
    }
    Monom res(degree, coeff - m.coeff);
    return res;
}
Monom Monom::operator*(const Monom& m)
{
    if (((degree) / 100 + (m.degree) / 100) > 9 || (((degree) / 10) % 10 + ((m.degree) / 10) % 10) > 9 || ((degree) % 10 + (m.degree) % 10) > 9)
    {
        throw "degree is out of range!";
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

Polinom::Polinom(const string& infix)
{
    this->infix = infix;
    char c;
    string tocken;
    tocken += infix[0];
    for (int i = 1; i < infix.size(); i++)
    {
        c = infix[i];
        if (c == '+')
        {
            Monom m(tocken);
            insert(m);
            tocken.clear();
            continue;
        }
        if (c == '-')
        {
            Monom m(tocken);
            insert(m);
            tocken = "-";
            continue;
        }
        tocken += c;
    }
    if (!(tocken.empty()))
    {
        Monom m(tocken);
        insert(m);
    }
}

Monom Polinom::getMonom()const
{
    int a = polinom.getCurr()->key.GetDegree();
    double b = polinom.getCurr()->key.GetCoeff();
    Monom m(a, b);
    return m;
}
Monom Polinom::last_smaller(const Monom m)
{
    polinom.reset();
    Monom a;
    if (polinom.getCurr() == nullptr)
    {
        return a;
    }
    while (!(polinom.is_ended()))
    {
        if (polinom.getCurr()->key <= m)
        {
            a = polinom.getCurr()->key;
        }
        polinom.next();
    }
    return a;
}
void Polinom::insert(Monom& m)
{
    TNode<Monom>* b;
    polinom.reset();
    if (polinom.getCurr() == nullptr)
    {
        b = new TNode<Monom>(m);
        polinom.push_front(b);
        return;
    }
    Monom a = last_smaller(m);
    if (m == a)
    {
        m = a + m;
        if (m.GetCoeff() == 0)
        {
            polinom.remove(a);
            return;
        }
        polinom.remove(a);
        a = last_smaller(m);
    }
    b = new TNode<Monom>(m);
    polinom.push_after(b, a);
}

bool Polinom::operator == (const Polinom& p) const
{
    return (polinom == p.polinom);
}
bool Polinom::operator != (const Polinom& p) const
{
    return !(*this == p);
}

Polinom Polinom::operator+(const Monom& m)
{
    Polinom copy(*this);
    Monom mcopy(m);
    copy.insert(mcopy);
    return copy;
}
Polinom Polinom::operator-(const Monom& m)
{
    Polinom copy(*this);
    Monom mcopy(m.GetDegree(), -m.GetDegree());
    copy.insert(mcopy);
    return copy;
}
Polinom Polinom::operator*(const Monom& m)
{
    Polinom copy(*this);
    Monom mcopy(m);
    copy.polinom.reset();
    while (!(copy.polinom.is_ended()))
    {
        copy.polinom.getCurr()->key = mcopy * copy.polinom.getCurr()->key;
        copy.polinom.next();
    }
    return copy;
}

Polinom Polinom::operator+(double a)
{
    Monom m(0, a);
    Polinom res;
    res = (*this) + m;
    return res;
}
Polinom Polinom::operator-(double a)
{
    Monom m(0, a);
    Polinom res;
    res = (*this) - m;
    return res;
}
Polinom Polinom::operator*(double a)
{
    Monom m(0, a);
    Polinom res;
    res = (*this) * m;
    return res;
}

Polinom Polinom::operator+(const Polinom& p)
{
    if (this == &p)
    {
        Polinom p1(p), res;
        res = *this + p1;
        return res;
    }
    Polinom copy(p), res(*this);
    copy.polinom.reset();
    while (!(copy.polinom.is_ended()))
    {
        Monom m = copy.getMonom();
        res = res + m;
        copy.polinom.next();
    }
    return res;
}
Polinom Polinom::operator-(const Polinom& p)
{
    if (this == &p)
    {
        Polinom res;
        return res;
    }
    Polinom res(p);
    res = res * (-1);
    res = res + (*this);
    return res;
}
Polinom Polinom::operator*(const Polinom& p)
{
    if (this == &p)
    {
        Polinom p1(p), res;
        res = *this * p1;
        return res;
    }
    Polinom copy(p), myself(*this), res;
    copy.polinom.reset();
    myself.polinom.reset();
    if ((myself.polinom.getCurr() == nullptr) || (copy.polinom.getCurr() == nullptr))
    {
        return *this;
    }
    while (!(copy.polinom.is_ended()))
    {
        Monom m = copy.getMonom();
        res = res + (myself * m);
        copy.polinom.next();
    }
    return res;
}

const Polinom& Polinom::operator = (const Polinom& p)
{
    if (this == &p)
    {
        return *this;
    }
    infix = p.infix;
    polinom = p.polinom;
    return *this;
}

double Polinom::operator()(double x, double y, double z)const
{
    double res = 0.0;
    Polinom copy(*this);
    copy.polinom.reset();
    if (copy.polinom.getCurr() == nullptr)
    {
        return res;
    }
    while (!(copy.polinom.is_ended()))
    {
        res += copy.polinom.getCurr()->key(x, y, z);
        copy.polinom.next();
    }
    return res;
}

