#include "list.h"
#include "tpolynom.h"
#include "tmonom.h"
#include <iostream>
#include <string>
using namespace std;

void calculate_polynomial(Polinom& p);

void handle_addition(Polinom& p);
void handle_subtraction(Polinom& p);
void handle_multiplication(Polinom& p);
void handle_evaluation(Polinom& p);

int main() {
    int option = 1;
    Polinom current_poly;

    while (option != 0) {
        try {
            switch (option) {
            case 1:
                cout << "Input polynomial:\n";
                {
                    string input;
                    cin >> input;
                    Polinom p(input);
                    calculate_polynomial(p);
                    current_poly = p;
                }
                break;
            case 2:
                calculate_polynomial(current_poly);
                break;
            default:
                throw invalid_argument("Invalid option");
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

        cout << "\n(2 = continue, 1 = new, 0 = exit)\n";
        cin >> option;
    }

    return 0;
}

void calculate_polynomial(Polinom& p) {
    cout << "Choose operation:\n"
        << "(+) sum\n"
        << "(-) subtract polynomial\n"
        << "(*) multiply\n"
        << "(#) evaluate\n";

    char op;
    cin >> op;

    try {
        switch (op) {
        case '+': handle_addition(p); break;
        case '-': handle_subtraction(p); break;
        case '*': handle_multiplication(p); break;
        case '#': handle_evaluation(p); break;
        default: throw invalid_argument("Invalid operator");
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void handle_addition(Polinom& p) {
    cout << "constant(0) or polynomial(1)?\n";
    char choice;
    cin >> choice;

    if (choice == '0') {
        double constant;
        cout << "Enter constant:\n";
        cin >> constant;
        cout << (p + constant);
    }
    else if (choice == '1') {
        cout << "Enter second polynomial:\n";
        string input;
        cin >> input;
        Polinom p1(input);
        cout << (p + p1);
    }
    else {
        throw invalid_argument("Invalid choice");
    }
}

void handle_subtraction(Polinom& p) {
    cout << "Enter second polynomial:\n";
    string input;
    cin >> input;
    Polinom p1(input);
    cout << (p - p1);
     
    
    
}

void handle_multiplication(Polinom& p) {
    cout << "constant(0) or polynomial(1)?\n";
    char choice;
    cin >> choice;

    if (choice == '0') {
        double constant;
        cout << "Enter constant:\n";
        cin >> constant;
        cout << (p * constant);
    }
    else if (choice == '1') {
        cout << "Enter second polynomial:\n";
        string input;
        cin >> input;
        Polinom p1(input);
        cout << (p * p1);
    }
    else {
        throw invalid_argument("Invalid choice");
    }
}

void handle_evaluation(Polinom& p) {
    double x, y, z;
    cout << "Value of x is: ";
    cin >> x;
    cout << "\nValue of y is: ";
    cin >> y;
    cout << "\nValue of z is: ";
    cin >> z;
    cout << "\n" << p(x, y, z);
}

