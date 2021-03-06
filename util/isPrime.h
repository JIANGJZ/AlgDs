#ifndef AlgDs_isPrime_h
#define AlgDs_isPrime_h

bool isPrime(int num) {
    if (num < 2) {
        return false;
    }
    
    for (int i = 2; i * i < num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
    
}

#endif
