#ifndef AlgDs_stack_conversion_h
#define AlgDs_stack_conversion_h
#include "v_stack.h"
#include "common.h"


void convert(VStack<char> &VS, int64 n, int base) {
    static char digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    while (n > 0) {
        VS.push(digit[n % base]);
        n /= base;
    }
    
}

#endif
