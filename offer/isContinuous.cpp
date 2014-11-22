#include <iostream>
#include <algorithm>

using namespace std;

int compare(const void* arg1, const void* arg2) {
    return *(int*)arg1 - *(int*)arg2;
}

class isZero {
public:
    bool operator() (int a){ return a == 0;}
};

bool isContinuous(int* data, int length) {
    if (data == nullptr || length < 0) {
        return false;
    }
    
    qsort(data, length, sizeof(int), compare);
    
    long zero_num = count_if(data, data+length, isZero());
    
    
    cout << zero_num << endl;
    
    
    int gap = 0;
    long start = zero_num;
    for (long i = start; i < length; i++) {
        gap += (data[i] - data[i - 1] - 1);
    }
    
    cout << gap << endl;
    if (zero_num >= gap) {
        return true;
    }
    else {
        return false;
    }
    
}

/*
int main()
{
    int data[6] = {0, 0, 1, 2, 5, 6};
    cout << isContinuous(data, 6) << endl;
}
*/