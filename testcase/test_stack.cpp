#include "v_stack.h"
#include "l_stack.h"
#include "stack_conversion.h"
#include "stack_parentheses.h"
#include "stack_infix.h"
#include "stack_rpn.h"


#include <iostream>

int main() {
    VStack<int> VS;
    VS.push(1);
    std::cout << VS.top() << std::endl;
    
    LStack<int> LS;
    LS.push(1);
    LS.push(3);
    std::cout << LS.pop() << std::endl;
    std::cout << LS.pop() << std::endl;
    
    VStack<char> VS_c;
    convert(VS_c, 4, 2);
    while (!VS_c.empty()) {
        std::cout << VS_c.pop();
    }
    std::cout << std::endl;
    
    
    
     char exp[4] = {'(', '[', ')', ']'};
     std::cout << parenthese(exp, 0, 4);
    
    
}
