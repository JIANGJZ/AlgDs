#ifndef AlgDs_stack_infix_h
#define AlgDs_stack_infix_h

#include "v_stack.h"
#include "fac.h"

#include <string>
#include <cmath>

using namespace std;

const int OPE_NUM = 9;

typedef enum {
    ADD, SUB, MUT, DIV, POW, FAC, L_P, R_P, EOS
} operator_t;

const char priority[OPE_NUM][OPE_NUM] = {
    //          |-------------------当前运算符-------------------|
    //          +     -     *     /     ^     !     (     )     \0
    /*  栈+  */ '>',  '>',  '<',  '<',  '<',  '<',  '<',  '>',  '>',
    
    /*  顶-  */ '>',  '>',  '<',  '<',  '<',  '<',  '<',  '>',  '>',
    
    /*  运*  */ '>',  '>',  '>',  '>',  '<',  '<',  '<',  '>',  '>',
    
    /*  算/  */ '>',  '>',  '>',  '>',  '<',  '<',  '<',  '>',  '>',
    
    /*  符^  */ '>',  '>',  '>',  '>',  '>',  '<',  '<',  '>',  '>',
    
    /*    !  */ '>',  '>',  '>',  '>',  '>',  '>',  '<',  '>',  '>',
    
    /*    (  */ '<',  '<',  '<',  '<',  '<',  '<',  '<',  '=',  ' ',
    
    /*    )  */ ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
    
    /*    \0 */ '<',  '<',  '<',  '<',  '<',  '<',  '<',  ' ',  '=',
};

char *removeSpace(char *s) {
    char *p = s;
    char *q = s;
    while(true) {
        while(isspace(*p)) {
            ++p;
        }
        if ('\0' == p) {
            q = '\0';
            return q;
        }
        q = p;
        ++q;
        ++p;
    }
}

void readNum(char *&p, VStack<float>& stk) {
    stk.push((float)(*p - '0'));
    while (isdigit(*(++p))) {
        stk.push(stk.pop() * 10 + (*p - '0'));
    }
    if('.' != *p) {
        return;
    }
    float fraction = 1;
    while (isdigit(*(++p))) {
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
    }
}

char getPriority(operator_t stack, operator_t current) {
    return priority[stack][current];
}

operator_t getRank(char op) {
    operator_t ret_val;
    switch (op) {
        case '+':
            ret_val = operator_t::ADD;
            break;
        case '-':
            ret_val = operator_t::SUB;
            break;
        case '*':
            ret_val = operator_t::MUT;
            break;
        case '/':
            ret_val = operator_t::DIV;
            break;
        case '^':
            ret_val = operator_t::POW;
            break;
        case '!':
            ret_val = operator_t::FAC;
            break;
        case '(':
            ret_val = operator_t::L_P;
            break;
        case ')':
            ret_val = operator_t::R_P;
            break;
        case '\0':
            ret_val = operator_t::EOS;
            break;
        default:
            exit(-1);
            break;
    }
    return ret_val;
}

float cacul(float a, float b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                exit(-1);
            }else {
                return a / b;
            }
        case '^':
            return pow(a, b);
        default:
            exit(-1);
    }
}

float cacul(float a, char op) {
    switch (op) {
        case '!':
            return (float)fac((int)a);
        default:
            exit(-1);
    }
}

float evaluete(char *s) {
    VStack<float> opnd;
    VStack<char> optr;
    optr.push('\0');
    while (!optr.empty()) {
        if (isdigit(*s)) {
            readNum(s, opnd);
        } else {
            operator_t rank_current = getRank(*s);
            operator_t rank_stack_top = getRank(optr.top());
            switch (getPriority(rank_stack_top, rank_current)) {
                case '<':
                    optr.push(*s);
                    ++s;
                    break;
                case '=':
                    optr.pop();
                    ++s;
                    break;
                case '>': {
                    char op = optr.pop();
                    if ( op == '!') {
                        float a = opnd.pop();
                        opnd.push(cacul(a, op));
                    } else {
                        float a = opnd.pop();
                        float b = opnd.pop();
                        opnd.push(cacul(a, b, op));
                    }
                }
                break;
                default:
                break;
            }
        }
    }
    return opnd.pop();
}



#endif
