#include <iostream>
#include <vector>
#include <cmath>
#include <random>

template<typename T> class integral {
protected:
    // TODO: Linke, rechte Integrationsgrenze vom typ T
    T xl; T xu;
    // TODO: Anzahl der Auswertepunkte
    int npoints;
    // ΤΟDO: Rein virtuelle Funktion computeArea, die einen Zeiger auf function<T> erhält
    virtual T computeArea(function<T>* f) = 0;
    integral(T xl, T xu, int npoints) : xl(xl), xu(xu), npoints(npoints) {
        // TODO: Implementierung des Konstruktors, der die Klassenvariablen setzt
    }

    // TODO: Rein virtuelle funktion print, die eine einen Zeiger auf ein function<T> Objekt entgegennimmt
    virtual void print(function<T>* f) = 0;
};

template<typename T> class montecarlo : public integral<T> {
    // TODO: Das Monte Carlo Integrale muss zusätzlich eine obere und untere Integrationsgrenze haben.
    // (vom Typ T)
    T yl; T yu;

    std::default_random_engine generator;

protected:
    T computeArea(function<T>* f) override {
        T area = 0;
        // TODO: implementiere computeArea, die einen Zeiger vom Typ function<T> als Eingabe annimmt.
        // Für den Monte Carlo Algorithmus, siehe Übung 6
        double points[this->npoints][2];
        std::uniform_real_distribution<T> distribution_x(this->xl, this->xu);
        std::uniform_real_distribution<T> distribution_y(yl, yu);

        for (size_t i = 0; i < this->npoints; i++) {
            points[i][0] = distribution_x(generator);
            points[i][1] = distribution_y(generator);
        }

        int m = 0;
        for (size_t i = 0; i < this->npoints; i++) {
            if (f->eval(points[i][0]) >= points[i][1]) {m++;}
        }
        
        double area_size = (this->xu-this->xl) * (yu-yl);
        double approx_integral = (m/static_cast<double>(this->npoints))*area_size;

        return approx_integral;
    } 
public:
    montecarlo(T xl, T xu, T yl, T yu, int npoints) : integral<T>(xl, xu, npoints), yl(yl), yu(yu) {
        // TODO: Implementierung des Konstruktors, der die Klassenvariablen setzt
    }
    ~montecarlo() {
        std::cout << "Deconstructor: Montecarlo Integral" << std::endl;
    }
    
    void print(function<T>* f) override {
        // TODO: Implementierung der rein virtuellen print-funktion aus der Basisklasse
        std::cout << "Integral(MC) in [" << this->xl << "," << this->xu << "] von ";
        f->print();
        std::cout << ":  " << computeArea(f) << std::endl;
    }
};

template<typename T> class riemann : public integral<T> {
protected:
    T computeArea(function<T>* f) override {
        T area = 0;
        // TODO: implementiere computeArea, die einen Zeiger vom Typ function<T> als Eingabe annimmt.
        // Für den Algorithmus der Rechteckregel, siehe Übung 6
        double approx_integral = 0;
        double column_width = (this->xu-this->xl) / this->npoints;

        for (size_t i = 0; i < this->npoints; i++) {
            approx_integral += f->eval((i+(0.5))*column_width) * column_width;
        }
        return approx_integral;
    }
public:
    riemann(T xl, T xu, int npoints) : integral<T>(xl, xu, npoints) {
        // TODO: Implementierung des Konstruktors, der die Klassenvariablen setzt
    }
    ~riemann() {
        std::cout << "Deconstructor: Riemann Integral" << std::endl;
    }

    void print(function<T>* f) override {
        // TODO: Implementierung der rein virtuellen print-funktion aus der Basisklasse
        std::cout << "Integral(RR) in [" << this->xl << "," << this->xu << "] von ";
        f->print();
        std::cout << ":  " << computeArea(f) << std::endl;
    }
};