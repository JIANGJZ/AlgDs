#include <iostream>

using namespace std;

int getFirstK(int* data, int k, int start, int end) {
    while (end >= start) {
        int mid_index = (end + start) / 2;
        int mid_data = data[mid_index];
        if (mid_data == k) {
            if((mid_index > 0 && data[mid_index - 1] != k) || mid_index == 0) {
                return mid_index;
            }
            else {
                end = mid_index - 1;
            }
        }
        else if(mid_data > k){
            end = mid_index - 1;
        }
        else {
            start = mid_index + 1;
        }
    }
    
    return -1;
}

int getLastK(int* data, int k, int start, int end) {
    while (end >= start) {
        int mid_index = (end + start) / 2;
        int mid_data = data[mid_index];
        
        if (k == mid_data) {
            if ((mid_index < end && data[mid_index - 1] != k) || (mid_index == end)) {
                return mid_index;
            }
            else {
                start = mid_index + 1;
            }
        }
        else if(mid_data > k){
            end = mid_index - 1;
        }
        else {
            start = mid_index + 1;
        }
        
    }
    return -1;
}

int getNumberOfK(int* data, int k, int length) {
    int number = 0;
    if (data != nullptr && length > 0) {
        int first = getFirstK(data, k, 0, length - 1);
        int last = getLastK(data, k, 0, length - 1);
        
        if (first != -1 && last != -1) {
            number = last - first + 1;
        }
    }
    return number;
}

/*
int main() {
    int data[7] = {1, 2, 2, 2, 2, 3, 7};
    cout << getFirstK(data, 2, 0, 6);
    cout << getLastK(data, 2, 0, 6);
    
}
*/