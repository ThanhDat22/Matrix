// Created by Thanh Dat Nguyen (tnrbf@umsystem.edu) on 2026-06-10

// Last modified by Thanh Dat Nguyen (tnrbf@umsystem.edu) on 2026-06-10

#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::string;
using std::pair;
class Number {
public:
    // Constructors
    Number(); // Default constructor, initialize to 0
    Number(const string&); // Constructor that takes a string representation of a number
    Number(const unsigned int); // Constructor that takes an unsigned integer

    // Setters
    void set_value(const string&); // Set the value of the number from a string

    // Operator overloads
    Number operator+(const Number&) const;
    Number operator-(const Number&) const;
    Number operator*(const Number&) const;
    Number operator/(const Number&) const;
    Number operator%(const Number&) const;

    Number& operator+=(const Number&);
    Number& operator-=(const Number&);
    Number& operator*=(const Number&);
    Number& operator/=(const Number&);
    Number& operator%=(const Number&);
    bool operator==(const Number&) const;
    bool operator!=(const Number&) const;
    bool operator<(const Number&) const;
    bool operator<=(const Number&) const;
    bool operator>(const Number&) const;
    bool operator>=(const Number&) const;

    // Member functions
    string to_string() const; // Convert the Bignum to its string representation
    void check_validity() const; // Check if the Number is valid (non-negative and no leading zeros)
    Number power(unsigned int) const; // Raise the Number to a non-negative integer power


private:
    // Data field
    vector<int> digits; // Stored value in the range 0 to 9

    // Helper functions
    void remove_leading_zeros(); // Remove leading zeros from the number
    bool is_zero() const; // Check if the number is zero
    Number multiply_by_digit(int) const; // Multiply the number by a single digit
    pair<Number, Number> divide_and_remainder(const Number&) const; // Divide the number by another Number and return the quotient and remainder
};
Number gcd(const Number&, const Number&); // Function to calculate the greatest common divisor of two Number objects

#endif // NUMBER_H