/*
    Scientific Calculator in C++
    -----------------------------
    Supports: +, -, *, /, modulus, power, square root, nth root,
              trigonometric functions (sin, cos, tan in degrees),
              inverse trigonometric functions,
              logarithms (base 10 and natural),
              exponential (e^x), factorial, and constants (pi, e).

    Compile:  g++ -std=c++17 -o scientific_calculator scientific_calculator.cpp
    Run:      ./scientific_calculator
*/

#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979323846;
const double E  = 2.71828182845904523536;

// ---------- Utility functions ----------

// Clears bad input from cin so the program doesn't loop forever on invalid input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads a double safely; returns true on success, false if input was invalid
bool readDouble(const string& prompt, double& value) {
    cout << prompt;
    cin >> value;
    if (cin.fail()) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a numeric value.\n";
        return false;
    }
    return true;
}

// Reads an integer safely (used for factorial)
bool readInt(const string& prompt, long long& value) {
    cout << prompt;
    cin >> value;
    if (cin.fail()) {
        clearInputBuffer();
        cout << "Invalid input. Please enter an integer value.\n";
        return false;
    }
    return true;
}

double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}

double radiansToDegrees(double radians) {
    return radians * (180.0 / PI);
}

// Iterative factorial to avoid recursion overhead/stack issues for larger n
double factorial(long long n) {
    double result = 1.0;
    for (long long i = 2; i <= n; ++i) {
        result *= static_cast<double>(i);
    }
    return result;
}

void printMenu() {
    cout << "\n===================================\n";
    cout << "        SCIENTIFIC CALCULATOR\n";
    cout << "===================================\n";
    cout << " 1. Addition (+)\n";
    cout << " 2. Subtraction (-)\n";
    cout << " 3. Multiplication (*)\n";
    cout << " 4. Division (/)\n";
    cout << " 5. Modulus (integer %)\n";
    cout << " 6. Power (x^y)\n";
    cout << " 7. Square Root\n";
    cout << " 8. Nth Root\n";
    cout << " 9. Sine (degrees)\n";
    cout << "10. Cosine (degrees)\n";
    cout << "11. Tangent (degrees)\n";
    cout << "12. Inverse Sine (asin, degrees)\n";
    cout << "13. Inverse Cosine (acos, degrees)\n";
    cout << "14. Inverse Tangent (atan, degrees)\n";
    cout << "15. Logarithm base 10\n";
    cout << "16. Natural Logarithm (ln)\n";
    cout << "17. Exponential (e^x)\n";
    cout << "18. Factorial (n!)\n";
    cout << "19. Show constants (pi, e)\n";
    cout << " 0. Exit\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    cout << fixed << setprecision(6);

    do {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid choice. Please enter a number from the menu.\n";
            continue;
        }

        double a = 0.0, b = 0.0, result = 0.0;
        long long ia = 0, ib = 0;
        bool ok = true;

        switch (choice) {
            case 1: // Addition
                ok = readDouble("Enter first number: ", a) &&
                     readDouble("Enter second number: ", b);
                if (ok) {
                    result = a + b;
                    cout << "Result: " << a << " + " << b << " = " << result << "\n";
                }
                break;

            case 2: // Subtraction
                ok = readDouble("Enter first number: ", a) &&
                     readDouble("Enter second number: ", b);
                if (ok) {
                    result = a - b;
                    cout << "Result: " << a << " - " << b << " = " << result << "\n";
                }
                break;

            case 3: // Multiplication
                ok = readDouble("Enter first number: ", a) &&
                     readDouble("Enter second number: ", b);
                if (ok) {
                    result = a * b;
                    cout << "Result: " << a << " * " << b << " = " << result << "\n";
                }
                break;

            case 4: // Division
                ok = readDouble("Enter numerator: ", a) &&
                     readDouble("Enter denominator: ", b);
                if (ok) {
                    if (b == 0.0) {
                        cout << "Error: Division by zero is undefined.\n";
                    } else {
                        result = a / b;
                        cout << "Result: " << a << " / " << b << " = " << result << "\n";
                    }
                }
                break;

            case 5: // Modulus (integer)
                ok = readInt("Enter first integer: ", ia) &&
                     readInt("Enter second integer: ", ib);
                if (ok) {
                    if (ib == 0) {
                        cout << "Error: Modulus by zero is undefined.\n";
                    } else {
                        cout << "Result: " << ia << " % " << ib << " = " << (ia % ib) << "\n";
                    }
                }
                break;

            case 6: // Power
                ok = readDouble("Enter base: ", a) &&
                     readDouble("Enter exponent: ", b);
                if (ok) {
                    result = pow(a, b);
                    if (isnan(result) || isinf(result)) {
                        cout << "Error: Result is undefined or out of range for these inputs.\n";
                    } else {
                        cout << "Result: " << a << " ^ " << b << " = " << result << "\n";
                    }
                }
                break;

            case 7: // Square root
                ok = readDouble("Enter number: ", a);
                if (ok) {
                    if (a < 0) {
                        cout << "Error: Square root of a negative number is not real.\n";
                    } else {
                        result = sqrt(a);
                        cout << "Result: sqrt(" << a << ") = " << result << "\n";
                    }
                }
                break;

            case 8: // Nth root
                ok = readDouble("Enter number: ", a) &&
                     readDouble("Enter root degree (n): ", b);
                if (ok) {
                    if (b == 0.0) {
                        cout << "Error: Root degree cannot be zero.\n";
                    } else if (a < 0 && fmod(b, 2.0) == 0.0) {
                        cout << "Error: Even root of a negative number is not real.\n";
                    } else {
                        // Handle negative base with odd root correctly
                        if (a < 0) {
                            result = -pow(-a, 1.0 / b);
                        } else {
                            result = pow(a, 1.0 / b);
                        }
                        cout << "Result: " << b << "th root of " << a << " = " << result << "\n";
                    }
                }
                break;

            case 9: // Sine (degrees)
                ok = readDouble("Enter angle in degrees: ", a);
                if (ok) {
                    result = sin(degreesToRadians(a));
                    cout << "Result: sin(" << a << " deg) = " << result << "\n";
                }
                break;

            case 10: // Cosine (degrees)
                ok = readDouble("Enter angle in degrees: ", a);
                if (ok) {
                    result = cos(degreesToRadians(a));
                    cout << "Result: cos(" << a << " deg) = " << result << "\n";
                }
                break;

            case 11: { // Tangent (degrees)
                ok = readDouble("Enter angle in degrees: ", a);
                if (ok) {
                    double cosVal = cos(degreesToRadians(a));
                    if (fabs(cosVal) < 1e-12) {
                        cout << "Error: Tangent is undefined at this angle.\n";
                    } else {
                        result = tan(degreesToRadians(a));
                        cout << "Result: tan(" << a << " deg) = " << result << "\n";
                    }
                }
                break;
            }

            case 12: // Inverse Sine
                ok = readDouble("Enter value (-1 to 1): ", a);
                if (ok) {
                    if (a < -1.0 || a > 1.0) {
                        cout << "Error: asin is only defined for values between -1 and 1.\n";
                    } else {
                        result = radiansToDegrees(asin(a));
                        cout << "Result: asin(" << a << ") = " << result << " degrees\n";
                    }
                }
                break;

            case 13: // Inverse Cosine
                ok = readDouble("Enter value (-1 to 1): ", a);
                if (ok) {
                    if (a < -1.0 || a > 1.0) {
                        cout << "Error: acos is only defined for values between -1 and 1.\n";
                    } else {
                        result = radiansToDegrees(acos(a));
                        cout << "Result: acos(" << a << ") = " << result << " degrees\n";
                    }
                }
                break;

            case 14: // Inverse Tangent
                ok = readDouble("Enter value: ", a);
                if (ok) {
                    result = radiansToDegrees(atan(a));
                    cout << "Result: atan(" << a << ") = " << result << " degrees\n";
                }
                break;

            case 15: // log base 10
                ok = readDouble("Enter number: ", a);
                if (ok) {
                    if (a <= 0) {
                        cout << "Error: Logarithm is only defined for positive numbers.\n";
                    } else {
                        result = log10(a);
                        cout << "Result: log10(" << a << ") = " << result << "\n";
                    }
                }
                break;

            case 16: // natural log
                ok = readDouble("Enter number: ", a);
                if (ok) {
                    if (a <= 0) {
                        cout << "Error: Natural logarithm is only defined for positive numbers.\n";
                    } else {
                        result = log(a);
                        cout << "Result: ln(" << a << ") = " << result << "\n";
                    }
                }
                break;

            case 17: // e^x
                ok = readDouble("Enter exponent x: ", a);
                if (ok) {
                    result = exp(a);
                    if (isinf(result)) {
                        cout << "Error: Result is too large to represent.\n";
                    } else {
                        cout << "Result: e^" << a << " = " << result << "\n";
                    }
                }
                break;

            case 18: // factorial
                ok = readInt("Enter a non-negative integer: ", ia);
                if (ok) {
                    if (ia < 0) {
                        cout << "Error: Factorial is not defined for negative numbers.\n";
                    } else if (ia > 170) {
                        cout << "Error: Value too large; result would overflow double precision.\n";
                    } else {
                        result = factorial(ia);
                        cout << "Result: " << ia << "! = " << result << "\n";
                    }
                }
                break;

            case 19: // constants
                cout << "pi = " << PI << "\n";
                cout << "e  = " << E << "\n";
                break;

            case 0:
                cout << "Exiting calculator. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please select an option from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}