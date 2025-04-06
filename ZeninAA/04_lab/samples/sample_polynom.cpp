#include "list.h"
#include "tpolynom.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    try {
        cout << "Enter the first polynomial:\n";
        string P1;
        cin >> P1;

        cout << "Enter the second polynomial:\n";
        string P2;
        cin >> P2;

        TPolynom pol1 = TPolynom(P1);
        TPolynom pol2 = TPolynom(P2);

        cout << "Your polinomials:\n";
        cout << "pol1:\n";
        cout << pol1.ToString() << "\n";

        cout << "pol2:\n";
        cout << pol2.ToString() << "\n";

        cout << "Addition (pol1 + pol2) :\n";
        cout << (pol1 + pol2).ToString() << "\n";

        cout << "Unary minus (-pol1) :\n";
        cout << (-pol1).ToString() << "\n";

        cout << "Subtraction (pol1 - pol2) :\n";
        cout << (pol1 - pol2).ToString() << "\n";

        cout << "Multiplication (pol1 * pol2) :\n";
        cout << (pol1 * pol2).ToString() << "\n";

        cout << "pol1 By X:\n";
        cout << (pol1.dx()).ToString() << "\n";

        cout << "pol1 By Y:\n";
        cout << (pol1.dy()).ToString() << "\n";

        cout << "pol1 By Z:\n";
        cout << (pol1.dz()).ToString() << "\n";

        double x, y, z;
        cout << "enter value of X: ";
        cin >> x;
        cout << "enter value of Y: ";
        cin >> y;
        cout << "enter value of Z: ";
        cin >> z;

        cout << "pol(x, y, z) => pol1(" << x << ", " << y << ", " << z << "):\n";
        cout << pol1(x, y, z);
    }
    catch (const exception ex) {
        cerr << ex.what() << "\n";
    }
    return 0;
}