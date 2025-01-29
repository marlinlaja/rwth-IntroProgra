#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <vector>
#include <chrono>

// Benutzte "Black Box" Funktion
template<typename T>
T f(const T& x) {
    if(x<=4) return 12;
    else if (x<=8) return -4*cos(3/4. * x * M_PI) + 8;
    else if (x<=12) return 4*sin((x-8.0) * M_PI) + 4;
    else return pow(x-13., 2) + 3.;
}


template<typename T>
T integral_mc(const int n, const T& xlower, const T& xupper, const T& ylower, const T& yupper) {  
  // TODO 2: Monte Carlo Integration mit std::random_engine_generator und std::uniform_real_distribution
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution_x(xlower, xupper);
  std::uniform_real_distribution<double> distribution_y(ylower, yupper);

  double points[n][2];

  for (size_t i = 0; i < n; i++) {
    points[i][0] = distribution_x(generator);
    points[i][1] = distribution_y(generator);
  }

  // punkte testen
  int m = 0;
  for (size_t i = 0; i < n; i++) {
    if (f(points[i][0]) >= points[i][1]) {m++;}
  }
  
  // geschätztes integral berechnen
  double area_size = (xupper-xlower) * (yupper-ylower);
  double approx_integral = (m/static_cast<double>(n))*area_size;

  return approx_integral;
}


template<typename T>
T integral_riemann(const int n, const T& xlower, const T& xupper) {
  // TODO 3: Recheckabschätzung
  double approx_integral = 0;
  double column_width = (xupper-xlower) / n;

  // summe von n rechtecken unter der funktion
  for (size_t i = 0; i < n; i++) {
    approx_integral += f((i+(0.5))*column_width) * column_width;
  }

  return approx_integral;
}


// Exakter Integralwert für X=[0,16]
double integral_exact() {
    // TODO 1: Bereche den exakten Wert
    double result = 0;
    result += 48; // [0, 4]
    result += 32; // (4, 8]
    result += 16; // (8, 12]
    result += 21.33333333; // (12, 16]

    return result;
}


template<typename T>
T error(const T& approx, const T& exact) {
  // TODO 4: berechne den relativen Fehler
  return fabs((approx-exact)/exact);
}


int main() {
  // TODO 5: Abfrage von Benutzereingaben und Ausgabe der gewünschten Ergebnisse
  using namespace std;

  int numTests = 5;
  vector<int> nValues(numTests, 0);

  vector<double> mc_approx(numTests, 0);
  vector<double> mc_error(numTests, 0);
  vector<double> rr_approx(numTests, 0);
  vector<double> rr_error(numTests, 0);

  bool mc = false;
  bool rr = false;

  cout << "Integral mit Monte Carlo Methode berechnen? (0: N, 1: Y): "; cin >> mc;
  cout << "Integral mit Rechteckverfahren berechnen? (0: N, 1: Y): "; cin >> rr;

  for (size_t i = 1; i <= numTests; i++) {
    nValues[i-1] = pow(10, i);
  }

  double exact = integral_exact();
  if (mc) {
    for (size_t i = 0; i < numTests; i++) {
      mc_approx[i] = integral_mc<double>(nValues[i], 0, 16, 0, 16);
      mc_error[i] = error(mc_approx[i], exact);
    }
    cout << "Berechnung mit Monte Carlo Methode abgeschlossen" << endl;
  }
  if (rr) {
    for (size_t i = 0; i < numTests; i++) {
      rr_approx[i] = integral_riemann<double>(nValues[i], 0, 16);
      rr_error[i] = error(rr_approx[i], exact);
    }
    cout << "Berechnung mit Rechteckverfahren abgeschlossen" << endl;
  }

  //Ausgabe Tabelle
  int width = 12;
  //Tabelle Kopfzeile
  cout << left << setw(width) << "n" << setw(width) << "SYMB" << setw(width);
  if (mc) {cout << "MC" << setw(width);};
  if (rr) {cout << "RR" << setw(width);};
  if (mc) {cout << "MC(err)" << setw(width);};
  if (rr) {cout << "RR(err)" << setw(width);};
  cout << endl;

  //Tabelle Zahlenwerte
  for (int i = 0; i < numTests; i++) {
    cout << left << setw(width) << nValues[i] << setw(width) << exact << setw(width);
    if (mc) {cout << mc_approx[i] << setw(width);};
    if (rr) {cout << rr_approx[i] << setw(width);};
    if (mc) {cout << mc_error[i] << setw(width);};
    if (rr) {cout << rr_error[i] << setw(width);};
    cout << endl;
  }
  return 0;
}
