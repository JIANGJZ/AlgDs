#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& vec, int target) {
        vector<vector<int>> result;
        sort(vec.begin(), vec.end());
        
        auto last = vec.end();
        for (auto a = vec.begin(); a < prev(last, 3); a++) {
            for (auto b = next(a); b < prev(last, 2); b++) {
                auto c = next(b);
                auto d = prev(last);
                
                while (c < d) {
                    if (*a + *b + *c + *d < target) {
                        ++c;
                    } else if(*a + *b + *c + *d > target) {
                        --d;
                    }else {
                        result.push_back({*a, *b, *c, *d});
                        ++c;
                        --d;
                    }
                }
            }
        }
        
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};

class Solution2 {
public:
    
};

int main() {
    Solution s;
    vector<int> vec = {1, -1, 3, 2, 4, 5, 7, 0, -2};
    vector<vector<int>> result = s.fourSum(vec, 0);
    for(auto i : result) {
        for(auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}
