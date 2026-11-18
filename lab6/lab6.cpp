#include "rational.h"
#include <iostream>
#include <limits>

int main() {
    std::cout << "Rational DLL client\n";
    Rational a(2, 3), b(5, 6);
    std::cout << "a = " << a.toString() << "; b = " << b.toString() << '\n';
    std::cout << "a + b = " << (a + b).toString() << '\n';
    std::cout << "a - b = " << (a - b).toString() << '\n';
    std::cout << "a * b = " << (a * b).toString() << '\n';
    std::cout << "a / b = " << (a / b).toString() << '\n';
    std::cout << "(a+b)*a = " << ((a + b) * a).toString() << '\n';
    std::cout << "a remains " << a.toString() << "; b remains " << b.toString() << '\n';
    std::cout << "6/-8 reduces to " << Rational(6, -8).toString() << '\n';
    std::cout << "0/5 reduces to " << Rational(0, 5).toString() << '\n';
    try { auto value = a / Rational(0); (void)value; }
    catch (const std::domain_error& e) { std::cout << "Rejected: " << e.what() << '\n'; }
    try { Rational invalid(3, 0); }
    catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
    try { auto value = Rational(std::numeric_limits<long long>::max()) + Rational(1); (void)value; }
    catch (const std::overflow_error& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}