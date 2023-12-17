#include <iostream>
#include <complex>
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
import Math;
using namespace std;
int main()
{
    int choice;
    cout << "vvedite 1 dlya re im, ili 2 dlay mod arg: ";
    cin >> choice;

    Complex c;

    if (choice == 1) {
        double re, im;
        cout << "vvedite re: ";
        cin >> re;
        cout << "vvedite im: ";
        cin >> im;

        c = Complex::FromAlgebraicForm(re, im);
    }
    else if (choice == 2) {
        double mod, arg;
        cout << "vvedite mod: ";
        cin >> mod;
        cout << "vvedite arg: ";
        cin >> arg;

        c = Complex::FromExponentialForm(mod, arg);
    }
    else {
        cout << "nepravilno" << endl;
        return 1;
    }

    cout << "vvedite rational v vide nom/denom: ";
    int nominator, denominator;
    char separator;
    cin >> nominator >> separator >> denominator;

    Rational r(nominator, denominator);

    double d;
    cout << "vvedite real number: ";
    cin >> d;

    cout << "f(" << c << ") = " << f(c) << endl;
    cout << "f(" << r << ") = " << f(r) << endl;
    cout << "f(" << d << ") = " << f(d) << endl;

    return 0;
}