#include "list.h"
#include "tpolynom.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    try {
        cout << "Input first polynom:\n";
        string P1;
        cin >> P1;

        cout << "Input second polynom:\n";
        string P2;
        cin >> P2;

        TPolynom pol1 = TPolynom(P1);
        TPolynom pol2 = TPolynom(P2);

        cout << "Your polinoms:\n";
        cout << "Polynom1:\n";
        cout << pol1.ToString() << "\n";

        cout << "Polynom2:\n";
        cout << pol2.ToString() << "\n";

        cout << "Sum of two polynoms (pol1 + pol2) :\n";
        cout << (pol1 + pol2).ToString() << "\n";

        cout << "Unary minus (-Polynom1) :\n";
        cout << (-pol1).ToString() << "\n";

        cout << "Subtraction (Polynom1 - Polynom2) :\n";
        cout << (pol1 - pol2).ToString() << "\n";

        cout << "Mult (Polynom1 * Polynom2) :\n";
        cout << (pol1 * pol2).ToString() << "\n";

        cout << "Polynom1 derivation by X:\n";
        cout << (pol1.dx()).ToString() << "\n";

        cout << "Polynom1 derivation by Y:\n";
        cout << (pol1.dy()).ToString() << "\n";

        cout << "Polynom1 derivation by Z:\n";
        cout << (pol1.dz()).ToString() << "\n";

        double x, y, z;
        cout << "Input value of X: ";
        cin >> x;
        cout << "Input value of Y: ";
        cin >> y;
        cout << "Input value of Z: ";
        cin >> z;

        cout << "polynom(x, y, z) => Polynom1(" << x << ", " << y << ", " << z << "):\n";
        cout << pol1(x, y, z);
    }
    catch (const exception ex) {
        cerr << ex.what() << "\n";
    }
    return 0;
}