/*
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int> &vec, int target) {
        int mingap = INT_MAX;
        int result = 0;
        sort(vec.begin(), vec.end());
        auto last = vec.end();
        
        for (auto a = vec.begin(); a < prev(last, 2); ++a) {
            auto b = next(a);
            auto c = prev(vec.end());
            while (b < c) {
                const int sum = *a + *b + *c;
                const int gap = abs(sum - target);
                if (gap < mingap) {
                    mingap = gap;
                    result = sum;
                }
                
                if (sum < target) {
                    ++b;
                } else {
                    --c;
                }
            }
        }
        
        return result;
    }
};

int main() {
    Solution s;
    vector<int> arr = {-1, 3, 1, 4, 3, 0};
    std::cout << s.threeSumClosest(arr, 12);
}
*/