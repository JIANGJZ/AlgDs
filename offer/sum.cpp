#include <iostream>

using namespace std;

class Temp
{
public:
    Temp() {
        ++N;
        Sum += N;
    };
    
    static void reset() {
        Sum = 0;
        N = 0;
    }
    
    static unsigned int getSum() {
        return Sum;
    }
    
private:
    static unsigned int N;
    static unsigned int Sum;
};


unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_Solution1(unsigned int n) {
    Temp::reset();
    
    Temp* a= new Temp[n];
    
    delete []a;
    
    a = NULL;
    
    return Temp::getSum();
}

class A;
A* Array[2];

class A {
public:
    virtual unsigned int Sum(unsigned int n) {
        return 0;
    }
};

class B : public A {
public:
    virtual unsigned int Sum(unsigned int n) {
        return Array[!!n]->Sum(n-1) + n;
    }
};

int Sum_Solution2(int n) {
    A a;
    B b;
    Array[0] = &a;
    Array[1] = &b;
    
    int value = Array[1]->Sum(n);
    
    return value;
    
}

typedef unsigned int (*fun) (unsigned int);

unsigned int Solution3_Terminator(unsigned int n) {
    return 0;
}

unsigned int Sum_Solution3(unsigned int n) {
    static fun f[2] = {Solution3_Terminator, Sum_Solution3};
    
    return n + f[!!n](n - 1);
}

template <unsigned int n>
struct Sum_Solution4
{
    enum Value {
        N = Sum_Solution4<n-1>::N + n
    };
    
};

template< >
struct Sum_Solution4<1>
{
    enum Value {
        N = 1
    };
};

int main() {
    cout << Sum_Solution1(5) << endl;
    cout << Sum_Solution2(5) << endl;
    cout << Sum_Solution3(5) << endl;
    cout << Sum_Solution4<5>::N << endl;
}