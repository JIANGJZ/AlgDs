#ifndef AlgDs_sqrt_h
#define AlgDs_sqrt_h

#include <climits>
#include <cmath>

double sqrt(int num) {
    if (num < 0) {
        return INT_MIN;
    }
    double err = 1e-15;
    
    double t = c;
    
    while (abs(t - c/t) > err * t) {
        t = (c/t + t) / 2.0;
    }
    
    return t;
    
}


#endif
