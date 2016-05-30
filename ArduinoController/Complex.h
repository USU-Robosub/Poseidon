#include "Arduino.h"

class Complex {
public:
    Complex(){
        real = 0;
        imaginary = 0;
    }

    Complex(float r, float i) {
        real = r;
        imaginary = i;
    }

    float Magnitude() {

        return (float)sqrt(real*real + imaginary * imaginary);
    }

    static Complex FromPolarCoordinates(float radius, float theta) {

        return new Complex(radius * cos(theta), radius * sin(theta));
    }

    Complex& operator +=(const Complex& modifier) {
        real += modifier.real;
        imaginary += modifier.imaginary;
        return *this;
    }

    friend Complex operator +(Complex first, const Complex& second) {
        first += second;
        return first;
    }

    friend Complex operator *(Complex first, const Complex& second) {
        return new Complex(
            (first.real * second.real     ) - (first.imaginary * second.imaginary),
            (first.real * second.imaginary) + (first.imaginary * second.real     ));
    }

    float real;
    float imaginary;
}
