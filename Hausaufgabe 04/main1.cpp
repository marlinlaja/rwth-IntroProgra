#include <iostream>

// TODO 1: Typgenerische Funktion f, die double zurückgibt
template <typename T1, typename T2>

double f(T1 a, T2 b) {
    double result = (static_cast<double>(a)/static_cast<double>(b)) * (static_cast<double>(b)/static_cast<double>(a));
    // result = (a/b) * (b/a); // Hier würden inkorrekte Resultate auftreten
    return result;
}

int main() {
    using namespace std;

    // TODO 2: initialisiere int i1, int i2, double d
    int i1 = 1;
    int i2 = 2;
    double d = 1.5;

    // TODO 3: Rufe "f" für die aufgelisteten Kombinationen auf
    cout << f(i1, i1) << endl;
    cout << f(i1, i2) << endl;
    cout << f(i1, d) << endl;
    cout << f(d, i1) << endl;
    cout << f(d, d) << endl;

    // TODO 4: Sind die Resultate wie erwartet? Warum können mathematisch inkorrekte Resultat auftreten?
    /*
    Die Resultate sind wie erwartet.
    Bei der Multiplikation von zwei Brüchen bei welchen Nenner und Zähler vertauscht sind, kürzen diese sich raus.

    Inkorrekte Resultate könnten dadurch auftreten, dass man die Typgenerischen Werte nicht als double castet.
    Es könnten zum Beispiel bei der Division von Integers Fehler auftreten, da das Ergebnis ebenfalls als Integer berechnet würde und die Nachkommastellen wegfallen.
    Für meine Beispielzahlen gäbe f(i1, i2) demnach ein falsches Ergebnis, da für zwei Integer (1/2) = 0 ergibt.
    */
}