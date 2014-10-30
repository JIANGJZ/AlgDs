/*
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
        
        int *max_left = new int[n];
        int *max_right = new int[n];
        
        for (int i = 1; i < n; i++) {
            max_left[i] = max(max_left[i-1], A[i-1]);
            max_right[n-i-1] = max(max_right[n-i], A[n-i]);
            
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            int height = min(max_left[i], max_right[i]);
            if (height > A[i]) {
                result += (height-A[i]);
            }
        }
        
        delete []max_left;
        delete []max_right;
        
        
        return result;
    }
};

class Solution2 {
public:
    int trap(int arr[], int n) {
        int max = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] > arr[max]) {
                max = i;
            }
        }
        
        int result = 0;
        int peak = 0;
        for (int i = 0; i < max; i++) {
            if (arr[i] > peak) {
                peak = arr[i];
            } else {
                result += peak - arr[i];
            }
        }
        
        int top = 0;
        for (int i = n-1; i > max; i--) {
            if (arr[i] > top) {
                top = arr[i];
            } else {
                result += top - arr[i];
            }
        }
        
        return result;
    }
};

class Solution3 {
public:
    int trap(int arr[], int n) {
        stack<pair<int, int>> s;
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            int height = 0;
            
            while (!s.empty()) {
                int stack_top_v = s.top().first;
                int stack_top_p = s.top().second;
                
                result += (min(arr[i], stack_top_v) - height)*(i - stack_top_p -1);
                
                height = stack_top_v;
                
                if (arr[i] < stack_top_v) {
                    break;
                } else {
                    s.pop();
                }
            }
            
            s.push(make_pair(arr[i], i));
        }
        
        return result;
    }
};

int main() {
    Solution s3;
    int arr[12] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << s3.trap(arr, 12);

}
*/