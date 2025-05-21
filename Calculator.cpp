#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

// Function to perform calculation
double calculate(double num1, double num2, char op, bool &valid) {
    double result;
    valid = true;

    switch(op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/':
            if (num2 == 0) {
                cout << "Error: Division by zero." << endl;
                valid = false;
            } else {
                result = num1 / num2;
            }
            break;
        case '%':
            result = fmod(num1, num2); break;
        case '^':
            result = pow(num1, num2); break;
        default:
            cout << "Invalid operator." << endl;
            valid = false;
    }

    return result;
}

// Function to save calculation to history.txt
void saveToHistory(const string &expression, double result) {
    ofstream file("history.txt", ios::app); // append mode
    if (file.is_open()) {
        file << expression << " = " << result << endl;
        file.close();
    }
}

// Function to display history
void showHistory() {
    ifstream file("history.txt");
    string line;

    cout << "\n====== Calculation History ======\n";
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No history found." << endl;
    }
    cout << "=================================\n";
}

int main() {
    string input;
    double num1, num2, result;
    char op;
    char again;

    do {
        cout << "Enter an expression (example: 5 * 6): ";
        getline(cin, input);

        stringstream ss(input);
        ss >> num1 >> op >> num2;

        bool valid = true;
        result = calculate(num1, num2, op, valid);

        if (valid) {
            cout << "Result: " << result << endl;
            saveToHistory(input, result);
        }

        cout << "Do you want to calculate again? (y/n): ";
        cin >> again;
        cin.ignore(); // clear input buffer
        cout << endl;

    } while (again == 'y' || again == 'Y');

    showHistory();
    cout << "Goodbye!" << endl;

    return 0;
}