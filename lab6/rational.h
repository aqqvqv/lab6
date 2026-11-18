#pragma once
#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#if defined(_WIN32)
#  if defined(RATIONAL_BUILD)
#    define RATIONAL_API __declspec(dllexport)
#  else
#    define RATIONAL_API __declspec(dllimport)
#  endif
#else
#  define RATIONAL_API
#endif

class RATIONAL_API Rational {
private:
    long long numerator_ = 0;
    long long denominator_ = 1;

    static long long magnitude(long long x);
    static long long gcd(long long a, long long b);
    static long long checkedAdd(long long a, long long b);
    static long long checkedMul(long long a, long long b);
    // Exact comparison without multiplication or floating-point rounding.
    static int comparePositive(long long a, long long b,
        long long c, long long d);
public:
    Rational();
    explicit Rational(long long n);
    Rational(long long n, long long d);
    Rational(const Rational& other);
    ~Rational();
    void Init(long long n, long long d);
    void Read();
    void Display() const;
    std::string toString() const;
    long long getNumerator() const;
    long long getDenominator() const;
    void reduce();
    Rational add(const Rational& other) const;
    Rational sub(const Rational& other) const;
    Rational mul(const Rational& other) const;
    Rational div(const Rational& other) const;
    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;
    bool equal(const Rational& other) const;
    bool less(const Rational& other) const;
    bool greate(const Rational& other) const;
};
#endif