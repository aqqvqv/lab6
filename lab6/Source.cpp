#include "rational.h"

Rational::Rational() = default;
Rational::Rational(long long n) { Init(n, 1); }
Rational::Rational(long long n, long long d) { Init(n, d); }
Rational::Rational(const Rational& other)
    : numerator_(other.numerator_), denominator_(other.denominator_) {
}
Rational::~Rational() = default;

long long Rational::magnitude(long long x) {
    return x < 0 ? -x : x;
}

long long Rational::gcd(long long a, long long b) {
    a = magnitude(a); b = magnitude(b);
    while (b != 0) {
        long long r = a % b;
        a = b; b = r;
    }
    return a;
}

long long Rational::checkedAdd(long long a, long long b) {
    const long long m = std::numeric_limits<long long>::max();
    if ((b > 0 && a > m - b) ||
        (b < 0 && a < -m - b))
        throw std::overflow_error("Integer overflow");
    return a + b;
}

long long Rational::checkedMul(long long a, long long b) {
    const long long m = std::numeric_limits<long long>::max();
    if (b != 0 && magnitude(a) > m / magnitude(b))
        throw std::overflow_error("Integer overflow");
    return a * b;
}

int Rational::comparePositive(long long a, long long b,
    long long c, long long d) {
    bool reverse = false;
    for (;;) {
        long long q1 = a / b, q2 = c / d;
        if (q1 != q2) {
            int result = q1 < q2 ? -1 : 1;
            return reverse ? -result : result;
        }
        long long r1 = a % b, r2 = c % d;
        if (r1 == 0 || r2 == 0) {
            int result = r1 == r2 ? 0 : (r1 == 0 ? -1 : 1);
            return reverse ? -result : result;
        }
        a = b; b = r1; c = d; d = r2;
        reverse = !reverse;
    }
}

void Rational::Init(long long n, long long d) {
    const long long low = std::numeric_limits<long long>::min();
    if (d == 0)
        throw std::invalid_argument("Denominator must not be zero");
    if (n == low || d == low)
        throw std::out_of_range("LLONG_MIN is not supported");
    if (d < 0) { n = -n; d = -d; }
    numerator_ = n; denominator_ = d;
    reduce();
}

void Rational::Read() {
    long long n, d;
    if (!(std::cin >> n >> d))
        throw std::invalid_argument("Expected two integers");
    Init(n, d);
}

void Rational::Display() const { std::cout << toString(); }

std::string Rational::toString() const {
    return std::to_string(numerator_) + "/" +
        std::to_string(denominator_);
}

long long Rational::getNumerator() const { return numerator_; }

long long Rational::getDenominator() const { return denominator_; }

void Rational::reduce() {
    long long g = gcd(numerator_, denominator_);
    numerator_ /= g; denominator_ /= g;
}

Rational Rational::add(const Rational& other) const {
    long long g = gcd(denominator_, other.denominator_);
    long long left = checkedMul(numerator_, other.denominator_ / g);
    long long right = checkedMul(other.numerator_, denominator_ / g);
    Rational result;
    result.Init(checkedAdd(left, right),
        checkedMul(denominator_, other.denominator_ / g));
    return result;
}

Rational Rational::sub(const Rational& other) const {
    Rational negative;
    negative.Init(-other.numerator_, other.denominator_);
    return add(negative);
}

Rational Rational::mul(const Rational& other) const {
    long long g1 = gcd(numerator_, other.denominator_);
    long long g2 = gcd(other.numerator_, denominator_);
    Rational result;
    result.Init(checkedMul(numerator_ / g1, other.numerator_ / g2),
        checkedMul(denominator_ / g2, other.denominator_ / g1));
    return result;
}

Rational Rational::div(const Rational& other) const {
    if (other.numerator_ == 0)
        throw std::domain_error("Division by zero rational");
    Rational reciprocal;
    reciprocal.Init(other.denominator_, other.numerator_);
    return mul(reciprocal);
}

bool Rational::equal(const Rational& other) const {
    return numerator_ == other.numerator_ &&
        denominator_ == other.denominator_;
}

bool Rational::less(const Rational& other) const {
    if ((numerator_ < 0) != (other.numerator_ < 0))
        return numerator_ < 0;
    int comparison = comparePositive(magnitude(numerator_), denominator_,
        magnitude(other.numerator_), other.denominator_);
    return numerator_ < 0 ? comparison > 0 : comparison < 0;
}

bool Rational::greate(const Rational& other) const { return other.less(*this); }

Rational Rational::operator+(const Rational& other) const { return add(other); }
Rational Rational::operator-(const Rational& other) const { return sub(other); }
Rational Rational::operator*(const Rational& other) const { return mul(other); }
Rational Rational::operator/(const Rational& other) const { return div(other); }