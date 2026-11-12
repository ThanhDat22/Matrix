#include "Matrix.h"
#include "Number.h"

#include <stdexcept>

using namespace std;

Number fibonacci_matrix(int);

int main() {
    int n;
    cout << "Enter the position of the Fibonacci number to compute: ";
    cin >> n;

    try {
        Number fib_n = fibonacci_matrix(n);
        cout << "Fibonacci number at position " << n << " is: " << fib_n.to_string() << endl;
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;

}

Number fibonacci_matrix(int n) {
    if (n < 0) {
        throw invalid_argument("Fibonacci is not defined for negative numbers.");
    }

    if (n == 0) {
        return Number("0");
    }
    if (n == 1) {
        return Number("1");
    }

    Matrix<Number> F(2, 2);
    F.set(0, 0, Number("1"));
    F.set(0, 1, Number("1"));
    F.set(1, 0, Number("1"));
    F.set(1, 1, Number("0"));

    // Calculates the nth power of the matrix
    Matrix<Number> fib = F.power(n);

    return fib.at(0, 1);
} // Time complexity: O(log(n))