#pragma once
#include <stdexcept>
#include <iostream>

inline int GCD(int a, int b) //euclidean
{
    if (b == 0) return a;
    return GCD(b, a % b);
}

class Rational
{
private:
    int _p;
    int _q;

public:
    Rational(int p = 0, int q = 1) 
    {
        if (q == 0) throw std::domain_error{ "Division by zero is not allowed" };
        this->_p = p;
        this->_q = q;
        this->get_signs();
    }

    int get_numerator() { return this->_p; }

    int get_denumerator() { return this->_q; }

    void simplify()
    {
        int gcd = GCD(this->_p, this->_q);
        this->_p /= gcd;
        this->_q /= gcd;
    }

    void get_signs()
    {
        if (this->_p <= 0 && this->_q <= 0)
        {
            this->_p = abs(this->_p);
            this->_q = abs(this->_q);
        }

        else if (this->_q <= 0)
        {
            this->_q = abs(this->_q);
            this->_p *= -1;
        }
    }

    void operator=(const Rational& c1) {

        this->_p = c1._p;
        this->_q = c1._q;
    }

    Rational operator +(const Rational& arg)
    {
        Rational result = Rational(this->_p * arg._q + arg._p * this->_q,
            this->_q * arg._q);
        result.simplify();
        return result;
    }

    Rational operator -(const Rational& arg)
    {
        Rational result = Rational(this->_p * arg._q - arg._p * this->_q, this->_q * arg._q);
        result.simplify();
        result.get_signs();
        return result;
    }

    Rational operator *(const Rational& arg)
    {
        Rational result = Rational(this->_p * arg._p, this->_q * arg._q);
        result.simplify();
        return result;
    }

    Rational operator /(const Rational& arg)
    {
        Rational result = Rational(this->_p * arg._q, this->_q * arg._p);
        result.simplify();
        return result;
    }

    bool operator ==(const Rational& arg)
    {
        return ((this->_p * arg._q) == (this->_q * arg._p));
    }

    bool operator !=(const Rational& arg)
    {
        return !((this->_p * arg._q) == (this->_q * arg._p));
    }

    bool operator <(const Rational& arg)
    {
        return ((this->_p * arg._q) < (this->_q * arg._p));
    }

    bool operator <=(const Rational& arg)
    {
        return ((this->_p * arg._q) <= (this->_q * arg._p));
    }

    bool operator >(const Rational& arg)
    {
        return ((this->_p * arg._q) > (this->_q * arg._p));
    }

    bool operator >=(const Rational& arg)
    {
        return ((this->_p * arg._q) >= (this->_q * arg._p));
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& arg) {
        //if (arg._q == 1) return os << arg._p;
        return os << arg._p << "/" << arg._q;
    }
};
