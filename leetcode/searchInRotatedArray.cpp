/*
#include <iostream>

using namespace std;
//可重复也可不可重复, 如果arr[first <= mid] 则只能不重复
class Solution {
public:
    int search(int arr[], int length, int target) {
        int first = 0;
        int last = length;
        while (first < last) {
            int mid = first + (last - first)/2;
            if (arr[mid] == target) {
                return mid;
            }
            if (arr[first] < arr[mid]) {
                if (arr[first] <= target && target < arr[mid]) {
                    last = mid;
                } else {
                    first = mid + 1;
                }
            }else{
                if (arr[mid] < target && target <= arr[last - 1]) {
                    first = mid + 1;
                } else {
                    last = mid;
                }
            }
        }
        return -1;
    }
};

class Solution2 {
public:
    int search(int arr[], int length, int target) {
        int first = 0;
        int last = length;
        while (first < last) {
            int mid = first + (last - first)/2;
            if (arr[mid] == target) {
                return mid;
            }
            if (arr[first] < arr[mid]) {
                if(arr[first] <= target && target < arr[mid]) {
                    last = mid;
                }else{
                    first = mid + 1;
                }
            }else if(arr[first] > arr[mid]) {
                if (arr[mid] < target && target <= arr[last - 1]) {
                    first = mid + 1;
                }else{
                    last = mid;
                }
            }else{
                first++;
            }
        }
        return -1;
    }
};

int main() {
    int arr1[7] = {4, 5, 6, 0, 1, 2, 3};
    int arr2[7] = {1, 2, 3, 3, 1, 1, 1};
    Solution s;
    Solution2 s2;
    cout << s.search(arr1, 7, 6) << endl;
    cout << s.search(arr2, 7, 1) << endl;
    cout << s2.search(arr2, 7, 1) << endl;
    return 0;
}
*/