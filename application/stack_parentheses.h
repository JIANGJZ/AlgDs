#ifndef AlgDs_stack_parentheses_h
#define AlgDs_stack_parentheses_h
#include "l_stack.h"
#include "common.h"

bool parenthese(const char exp[], int lo, int hi) {
    LStack<char> LS;
    for (int i = lo; i < hi; i++) {
        if ('(' == exp[i] || '[' == exp[i] || '{' == exp[i]) {
            LS.push(exp[i]);
        } else if ('(' == LS.top() && ')' == exp[i]) {
            LS.pop();
        } else if ('[' == LS.top() && ']' == exp[i]) {
            LS.pop();
        } else if ('{' == LS.top() && '}' == exp[i]) {
            LS.pop();
        } else {
            return false;
        }
    }
    return LS.empty();
}

#endif
