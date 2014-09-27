#ifndef AlgDs_stack_rpn_h
#define AlgDs_stack_rpn_h

#include "v_stack.h"
#include "stack_infix.h"


void infixToRpn(char *infix, char *rpn) {
    VStack<char> optr;
    optr.push('\0');
    int j = 0;
    int i = 0;
    while(!optr.empty()){
        if (isdigit(infix[i]) || infix[i] == '.') {
            rpn[j++] = infix[i++];
        } else {
            if (i != 0 && isdigit(infix[i-1])) {
                rpn[j++] = ' ';
            }
            operator_t stack_top = getRank(optr.top());
            operator_t current = getRank(infix[i]);
            switch (getPriority(stack_top, current)) {
                case '<':
                    optr.push(infix[i]);
                    i++;
                    break;
                case '=':
                    optr.pop();
                    i++;
                    break;
                case '>': {
                    char op = optr.pop();
                    rpn[j++] = op;
                    rpn[j++] = ' ';
                }
                    break;
                default:
                    exit(-1);
                    break;
            }
        }
    }
    rpn[j++] = '\0';
    
}

float rpn_evaluate(char* rpn) {
    VStack<float> stk;
    for (int i = 0; rpn[i] != '\0'; i++) {
        if (isdigit(rpn[i])) {
            stk.push(rpn[i] - '0');
            while (isdigit(rpn[++i])) {
                stk.push(stk.pop() * 10 + rpn[i]);
            }
            if (rpn[i] == '.') {
                int faction = 1;
                while (isdigit(rpn[++i])) {
                    stk.push(stk.pop() + rpn[i] * (faction /= 10));
                }
            }
        } else if(rpn[i] == ' ') {
            continue;
        }else{
            if(rpn[i] == '!'){
                float op1 = stk.pop();
                float result = cacul(op1, rpn[i]);
                stk.push(result);
            } else {
                float op1 = stk.pop();
                float op2 = stk.pop();
                float result = cacul(op1, op2, rpn[i]);
                stk.push(result);
            }
        }
    }
    return 0.0;
}


#endif
