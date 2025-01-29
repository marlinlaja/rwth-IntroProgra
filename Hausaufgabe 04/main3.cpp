#include <iostream>
#include <cmath>
#include <cassert>

int main() {
    
    // TODO: In der Kommandozeile wird die Anzahl der Bits einer Binärzahl entgegengenommen.
    //       Deren Bits werden dann nacheinander als Eingaben entgegengenommen.
    //       Schließlich wird die entsprechende Dezimalzahl in der Kommandozeile ausgegeben.
    using namespace std;

    double input;
    cout << "Anzahl der bits: "; cin >> input;
    assert(input > 0 && input == ceil(input)); // sicherstellen, dass Eingabe ein positiver Integer
    int n = static_cast<int>(input);

    unsigned int result = 0;

    bool current_bit;
    for (int i = 1; i <=n; i++) {
        // einzelnes abfragen der bits (links nach rechts)
        cout << i << ". Bit (0 oder 1): "; cin >> current_bit;
        if (current_bit == true) {
            result += pow(2, n-i);
        }
    }
    cout << "Ausgabe: " << result;
}