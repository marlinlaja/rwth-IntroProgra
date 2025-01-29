#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

template<typename T> class function {
public:
    virtual T eval(const T& x) const = 0;
    // TODO: Pure virtual und const function für print 
    virtual void print() const = 0;

};

template<typename T> class polynom : public function<T> {
    // TODO: gespeicherte Klassenvariablen
    const int degree;
    const std::vector<T> p;
public:

    polynom(int degree, const std::vector<T>& p) : degree(degree), p(p) {
        // TODO: Implementierung des Konstruktors, der die Klassenvariablen setzt
    }
    ~polynom() {
        std::cout << "Deconstructor: Polynom Funktion" << std::endl;
    }

    T eval(const T& x) const override {
        // TODO: x auswerten mit Polynom gegebener Parameter
        T result = 0;
        for (size_t i = 0; i < p.size(); i++)
        {
            result += p[i] * pow(x, i);
        }
        return result;
    }
    void print() const override {
        // TODO: Funktion algebraisch auf der Kommandozeile 
        std::cout << "f(x) = ";
        std::cout << p[0];
        for (size_t i = 1; i <= degree; i++)
        {
            std::cout << " + ";
            std::cout << p[i];
            if (i != 0) {
                std::cout << " * x^" << i;
            }
        }
    }
};

template<typename T> class exponential : public function<T> {
    // TODO: gespeicherte Klassenvariablen
    const T a;
    const T b;
    const T c;
public: 

    exponential(T a, T b, T c) : a(a), b(b), c(c) {
        // TODO: Implementierung des Konstruktors, der die Klassenvariablen setzt
    }
    ~exponential() {
        std::cout << "Deconstructor: Exponential Funktion" << std::endl;
    }

    T eval(const T& x) const override { 
        // TODO: Auswerten von Polynom
        T result = a * exp(b*x) + c;
        return result;
    }

    void print() const override {
        // TODO: Funktion algebraisch auf der Kommandozeile ausgeben
        std::cout << "f(x) = " << a << " * exp(" << b << " * x) + " << c;
    }
};
