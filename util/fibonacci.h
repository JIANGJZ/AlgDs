#ifndef AlgDs_Fibonacci_h
#define AlgDs_Fibonacci_h

class Fib {
private:
    int f;
    int g;
public:
    Fib(int n) {
        f = 0;
        g = 1;
        while (n--) {
            next();
        }
    }
    
    int next() {
        g = f + g;
        f = g - f;
        return g;
    }
    
    int prev() {
        g = g - f;
        f = f - g;
        return  g;
    }
    
    int get() {
        return g;
    }
};

#endif
