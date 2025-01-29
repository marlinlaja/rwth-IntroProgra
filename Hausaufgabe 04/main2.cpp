#include <iostream>
#include <cmath>
#include <cassert>

int main() {
    
    // TODO 1: Binärdarstellung von 69 und -31 in 8-bit

    // 69  =  0100 0101
    // Rechnung: 2^6 + 2^2 + 2^0 = 64 + 4+ 1 = 69

    // -31 =  1110 0001 (Zweierkomplement)
    // Rechnung: 31 = 0000 0111 (analog zu 69) -> -31 = 1110 0001 (flippen und +1)


    // TODO 2: Nimm eine positive Zahl als int als Eingabe in der Kommandozeile entgegen.
    //         Berechne Anzahl der Bits mittels log und ceil aus cmath.
    //         Dann Erzeuge die Ausgabe der dazugehörigen  Binärzahl 
    using namespace std;

    double input;
    cout << "Eingabe Zahl: "; cin >> input;
    assert(input > 0 && input == ceil(input)); // sicherstellen, dass Eingabe ein positiver Integer
    int z = static_cast<int>(input);

    int n = ceil(log(z + 1) / log(2)); // anzahl der benötigten bits n

    // ausgabe der binärzahl
    cout << "Ausgabe: ";
    for (int i = n-1; i >= 0; i--) {
        
        if (pow(2, i) <= z) {
            cout << '1';
            z -= pow(2, i);
        } else {
            cout << '0';
        }
    }
}