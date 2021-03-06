#include <iostream>
#include <math.h>

class Complex {
    private:  
        double real, img;

    public:  
        Complex(double real, double img): real(real), img(img) {}

        Complex operator+(const Complex& c);
        Complex operator+(const char* str);
        Complex operator-(const Complex& c);
        Complex operator*(const Complex& c);
        Complex operator/(const Complex& c);
        Complex operator=(const Complex& c);
        Complex operator>>=(const double fn(double a));

        friend std::ostream& operator<<(std::ostream& os, const Complex& c);
        
        void println();
};

void Complex::println() {std::cout<<real<<" + "<<"("<<img<<")"<<std::endl;}
Complex Complex::operator+(const Complex& c) {
    Complex temp(real + c.real, img + c.img);
    return temp;
}
Complex Complex::operator-(const Complex& c) {
    Complex temp(real - c.real, img - c.img);
    return temp;
}
Complex Complex::operator*(const Complex& c) {
    Complex temp(
        real * c.real - img * c.img,
        real * c.img + img * c.real);
    return temp;
}
Complex Complex::operator/(const Complex& c) {
    Complex temp(
    (real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
    (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
    return temp;
}
Complex Complex::operator=(const Complex& c) {
    this -> real = c.real;
    this -> img = c.img;
    return *this;
}

// iostream overload
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << " , " << c.img << ") ";
    return os;
}

// TODO
// Give function as parameter
Complex Complex::operator>>=(const double fn(double)) {
    this -> real = fn(this -> real);
    this -> img = fn(this -> img);
    return *this;
}

double fn(double dd) {
    return dd * 3.141592;
}

int main() {
    Complex a(1.0, 2.0);
    Complex b(3.0, -2.0);
    Complex c(0.0, 0.0);

    c = a * b + a / b + a + b;
    std::cout << c << std::endl;



}