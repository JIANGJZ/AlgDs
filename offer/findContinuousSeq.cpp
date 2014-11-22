#include <iostream>

using namespace std;

void print(int small, int big) {
    for (int i = small; i <= big; i++) {
        cout << i << " ";
    }
    cout << endl;
}

void findContinuousSeq(int sum) {
    if (sum < 3) {
        return;
    }
    
    int small = 1;
    int big = 2;
    int middle = (sum + 1) / 2;
    int current_sum = small + big;
    
    while (small < middle) {
        
        if (current_sum == sum) {
            print(small, big);
        }
        
        while (current_sum > sum && small < middle) {
            current_sum -= small;
            small++;
            
            if (current_sum == sum) {
                print(small, big);
            }
            
        }
        
        big++;
        current_sum += big;
    }
    
    
}

/*
int main() {
    findContinuousSeq(15);
}
*/