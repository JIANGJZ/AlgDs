#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &vec) {
        auto begin = vec.rbegin();
        auto end = vec.rend();
        
        auto privot = begin;
        
        while (privot != end && *privot <= *next(privot)) {
            privot++;
        }
        
        cout << *privot << endl;
        cout << *prev(end) << endl;
        
        if(privot != prev(end)) {
            privot++;
            auto change = find_if(begin, privot, bind1st(less<int>(), *privot));
            swap(*change, *privot);
            reverse(begin, privot);
        } else {
            reverse(vec.begin(), vec.end());
        }
        
    }
};

int main() {
    vector<int> vec = {6, 8, 7, 4, 3, 2};
    vector<int> vec2 = {1, 2, 3, 4};
    Solution s;
    s.nextPermutation(vec2);
    for(auto i : vec2) {
        cout << i << " ";
    }
}