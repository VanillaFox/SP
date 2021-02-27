#include<iostream>
#include<cmath>
#include"mlisp.h"

extern double a;
extern double b;
extern double total__iterations;
extern double mphi;
extern double tolerance;
extern double total__iterations;
extern double xmin;

double fun(double x);
double golden__start(double a, double b);
double __KMS__try(double a, double b, double xa, double ya, double xb, double yb);
double golden__section__search(double a, double b);
bool close__enought_Q(double x, double y);

double a = 3.;
double b = 5.;
double mphi = (3. - sqrt(5.)) * 1. / 2.;
double tolerance = 0.001;
double total__iterations = 0.;
double xmin = 0.;

double fun(double x) {
    x = x - 17. / 18.;
    return sin(2. * x - 0.25 * pi) + log(x + 1.) + x - 0.5;
}

double golden__section__search(double a, double b) {
    {
        double xmin = (a < b) ? golden__start(a, b) : golden__start(b, a);
        newline();
        return xmin;
    }
}

double golden__start(double a, double b) {
    total__iterations = 0.;
    {
        double
            xa(a + (mphi * (b - a))),
            xb(b + (-mphi * (b - a)));
        return __KMS__try(a, b, xa, fun(xa), xb, fun(xb));
    }
}

double __KMS__try(double a, double b, double xa, double ya, double xb, double yb) {
    return close__enought_Q(a, b) ? ((a + b) * 0.5) :
        ((display("+"),
        total__iterations = total__iterations + 1.,
        (ya < yb ? (b = xb,
            xb = xa,
            yb = ya,
            xa = a + (mphi * (b - a)),
            __KMS__try(a, b, xa, fun(xa), xb, yb))
            : (a = xa,
            xa = xb,
            ya = yb,
            xb = b - (mphi * (b - a)),
            __KMS__try(a, b, xa, ya, xb, fun(xb))))));
}

bool close__enought_Q(double x, double y) {
    return (abs_(x - y) < tolerance);
}

int main()
{
    xmin = golden__section__search(a, b);
    display("Interval=\t[");
    display(a);
    display(", ");
    display(b);
    display("]\n");
    display("Total number of iteranions=");
    display(total__iterations);
    display("\n xmin=\t\t");
    display(xmin);
    display("\n f(xmin)=\t");
    display(fun(xmin));
}
