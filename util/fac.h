#ifndef AlgDs_fac_h
#define AlgDs_fac_h

#include "common.h"

int64 fac(int n) {
    int result = 0;
    for (int i = n; i > 1; i--) {
        result = result * i;
    }
    return result;
}

#endif
