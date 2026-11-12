// Created by Thanh Dat Nguyen (tnrbf@umsystem.edu) on 2026-06-10

// Last modified by Thanh Dat Nguyen (tnrbf@umsystem.edu) on 2026-06-11

#include "Number.h"

#include <iostream>

using std::cout;

// Constructors

// Default constructor, initialize to 0
Number::Number() {
    digits.push_back(0);
}

Number::Number(const string& number_string) {
    for (char c : number_string) {
        digits.push_back(c - '0'); // Convert char to int
    }
    remove_leading_zeros();
} // Time complexity: O(n)

Number::Number(const unsigned int number) {
    if (number == 0) {
        digits.push_back(0);
    } else {
        unsigned int n = number;
        while (n > 0) {
            digits.insert(digits.begin(), n % 10);
            n /= 10;
        }
    }
} // Time complexity: O(log(number))

// Setters
void Number::set_value(const string& number_string) {
    digits.clear();
    for (char c : number_string) {
        digits.push_back(c - '0'); // Convert char to int
    }
    remove_leading_zeros();
} // Time complexity: O(n)

// Member functions
void Number::remove_leading_zeros() {
    while (digits.size() > 1 && digits[0] == 0) {
        digits.erase(digits.begin());
    }
} // Time complexity: O(n)

bool Number::is_zero() const {
    return digits.size() == 1 && digits[0] == 0;
} // Time complexity: O(1)

Number& Number::operator+=(const Number& other) {
    *this = *this + other;
    return *this;
} // Time complexity: O(max(n, m))

Number& Number::operator-=(const Number& other) {
    *this = *this - other;
    return *this;
} // Time complexity: O(max(n, m))

Number& Number::operator*=(const Number& other) {
    *this = *this * other;
    return *this;
} // Time complexity: O(n * m)

Number& Number::operator/=(const Number& other) {
    *this = *this / other;
    return *this;
} // Time complexity: O(n * m)

Number& Number::operator%=(const Number& other) {
    *this = *this % other;
    return *this;
} // Time complexity: O(n * m)

Number Number::power(unsigned int exponent) const {
    Number result("1");
    Number base = *this;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
} // Time complexity: O(log(exponent) * n * m)

// Operator overloads
bool Number::operator == (const Number& other) const {
    return digits == other.digits;
} // Time complexity: O(n)

bool Number::operator != (const Number& other) const {
    return !(*this == other);
} // Time complexity: O(n)

bool Number::operator < (const Number& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
} // Time complexity: O(n)

bool Number::operator <= (const Number& other) const {
    return *this < other || *this == other;
} // Time complexity: O(n)

bool Number::operator > (const Number& other) const {
    return !(*this <= other);
} // Time complexity: O(n)

bool Number::operator >= (const Number& other) const {
    return !(*this < other);
} // Time complexity: O(n)

Number Number::operator + (const Number& other) const {
    Number result;
    result.digits.clear();

    int carry = 0;
    int i = digits.size() - 1;
    int j = other.digits.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += digits[i];
            --i;
        }
        if (j >= 0) {
            sum += other.digits[j];
            --j;
        }
        result.digits.insert(result.digits.begin(), sum % 10);
        carry = sum / 10;
    }
    result.remove_leading_zeros();
    return result;
} // Time complexity: O(max(n, m))

Number Number::operator - (const Number& other) const {
    if (*this < other) {
       cout << "Unsupported: Negative number.\n";
        return Number();
    }

    Number  result;
    result.digits.clear();

    int borrow = 0;
    int i = digits.size() - 1;
    int j = other.digits.size() - 1;

    while (i >= 0 || j >= 0) {
        int diff = (i >= 0 ? digits[i] : 0) - (j >= 0 ? other.digits[j] : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.insert(result.digits.begin(), diff);
        --i;
        --j;
    }
    result.remove_leading_zeros();
    return result;
} // Time complexity: O(max(n, m))

Number Number::multiply_by_digit(int digit) const {
    Number result;
    result.digits.clear();

    if (digit == 0 || is_zero()) {
        return Number();
    }

    int carry = 0;
    for (int i = digits.size() - 1; i >= 0; --i) {
        int product = digits[i] * digit + carry;
        result.digits.insert(result.digits.begin(), product % 10);
        carry = product / 10;
    }

    while (carry > 0) {
        result.digits.insert(result.digits.begin(), carry % 10);
        carry /= 10;
    }
    result.remove_leading_zeros();
    return result;
} // Time complexity: O(n)

Number Number::operator * (const Number& other) const {
    Number result;

    int zeros = 0;
    for (int i = other.digits.size() - 1; i >= 0; --i) {
        Number temp = multiply_by_digit(other.digits[i]);
        for (int j = 0; j < zeros; ++j) {
            temp.digits.push_back(0);
        }
        result = result + temp;
        ++zeros;
    }
    result.remove_leading_zeros();
    return result;
} // Time complexity: O(n * m)

pair<Number, Number> Number::divide_and_remainder(const Number& divisor) const {
    if (divisor == Number()) {
        cout << "Error: Divide by zero.\n";
        return {Number(), Number()};
    }

    Number quotient;
    quotient.digits.clear();
    Number remainder;

    for (size_t i = 0; i < digits.size(); ++i) {
        remainder.digits.push_back(digits[i]);
        remainder.remove_leading_zeros();

        int count = 0;
        while (remainder >= divisor) {
            remainder = remainder - divisor;
            ++count;
        }
        quotient.digits.push_back(count);
    }
    quotient.remove_leading_zeros();
    return {quotient, remainder};
} // Time complexity: O(n * m)

Number Number::operator / (const Number& other) const {
    return divide_and_remainder(other).first;
} // Time complexity: O(n * m)

Number Number::operator % (const Number& other) const {
    return divide_and_remainder(other).second;
} // Time complexity: O(n * m)

Number gcd(const Number& a, const Number& b) {
    if (b == Number()) {
        return a;
    }
    return gcd(b, a % b);
} // Time complexity: O(log(min(n, m)))

string Number::to_string() const {
    string result;
    for (int digit : digits) {
        result += (digit + '0'); // Convert int to char
    }
    return result;
} // Time complexity: O(n)

void Number::check_validity() const {
    if (digits.empty()) {
        cout << "Invalid Number: Empty digits.\n";
    }
    if (digits.size() > 1 && digits[0] == 0) {
        cout << "Invalid Number: Leading zeros.\n"; 
    }
    for (int digit : digits) {
        if (digit < 0 || digit > 9) {
            cout << "Invalid Number: Digits must be between 0 and 9.\n";            
        }
    }
} // Time complexity: O(n)