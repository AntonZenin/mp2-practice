#include "tpolynom.h"
#include <math.h>

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
            insertion(m);
            tocken.clear();
            continue;
        }
        if (c == '-')
        {
            Monom m(tocken);
            insertion(m);
            tocken = "-";
            continue;
        }
        tocken += c;
        
    }
    if (!(tocken.empty()))
    {
        Monom m(tocken);
        insertion(m);
    }
}



Monom Polinom::getMonom()const
{
    int a = polinom.getCurr()->key.GetDegree();
    double b = polinom.getCurr()->key.GetCoeff();
    Monom m(a, b);
    return m;
}

Monom Polinom::last(const Monom m)
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

void Polinom::insertion(Monom& m)
{
    TNode<Monom>* b;
    polinom.reset();
    if (polinom.getCurr() == nullptr)
    {
        b = new TNode<Monom>(m);
        polinom.push_front(b);
        return;
    }
    Monom a = last(m);
    if (m == a)
    {
        m = a + m;
        if (m.GetCoeff() == 0)
        {
            polinom.remove(a);
            return;
        }
        polinom.remove(a);
        a = last(m);
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
    copy.insertion(mcopy);
    return copy;
}
Polinom Polinom::operator-(const Monom& m)
{
    Polinom copy(*this);
    Monom mcopy(m.GetDegree(), -m.GetDegree());
    copy.insertion(mcopy);
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



