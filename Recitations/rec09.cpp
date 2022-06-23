/*
 * Jiezhi Winston Zuo-yu
 * rec09.cpp
 */

#include <iostream>
using namespace std;

int gcd(int x, int y);
class Rational {
    friend istream& operator>>(istream& is, Rational& rhs);
    friend ostream& operator<<(ostream& os,const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    Rational();
    Rational(int num);
    Rational(int num, int den);
    Rational& operator+= (const Rational& rhs);
    Rational& operator++();
    Rational operator++(int dummy);
    void changeNeg();
    void normRash();
    explicit operator bool() const;
private:
    int numerator, denominator;
};

Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator > (const Rational& lhs, const Rational& rhs);
bool operator >= (const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int dummy);

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    cout << "a + one: " << (a + one) << endl;

    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;

    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

Rational::Rational() : numerator(1), denominator(1) {}
Rational::Rational(int num) : numerator(num), denominator(1) {}
Rational::Rational(int num, int den) : numerator(num), denominator(den) {
    normRash();
    changeNeg();
}
int gcd(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}

Rational Rational::operator++(int dummy) {
    Rational result(*this);
    *this += 1;
    return result;
}

ostream& operator<<(ostream& os,const Rational& rhs) {
    os << rhs.numerator << "/" << rhs.denominator << endl;
    return os;
}

istream& operator>>(istream& is, Rational& rhs) {
    char slash;
    is >> rhs.numerator >> slash >> rhs.denominator;
    rhs.normRash();
    rhs.changeNeg();
    return is;
}

void Rational::changeNeg() {
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

void Rational::normRash() {
    int div = gcd(numerator, denominator);
    numerator = numerator/div;
    denominator = denominator/div;
}

Rational& Rational::operator+=(const Rational& rhs){
    numerator *= rhs.denominator;
    numerator += rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normRash();
    changeNeg();
    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    cout << result << endl << rhs << endl;
    result += rhs;
    return result;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs.numerator*rhs.denominator < rhs.numerator*lhs.denominator);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs==rhs);
}

Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}

Rational operator--(Rational& lhs, int dummy) {
    Rational result(lhs);
    lhs += -1;
    return result;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator > (const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs || lhs == rhs);
}

bool operator >= (const Rational& lhs, const Rational& rhs) {
    return (lhs > rhs || lhs == rhs);
}

Rational::operator bool() const {
    return (numerator != 0);
}

