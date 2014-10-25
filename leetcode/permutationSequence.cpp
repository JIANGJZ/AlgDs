/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    string findKthPermutaion(int n, int k) {
        vector<char> s(n, '0');
        for(int i = 0; i < s.size(); i++) {
            s[i] += i + 1;
        }
        
        for (int i = 0; i < k - 1; i++) {
            nextPermutation(s);
        }
        
        string ret(s.begin(), s.end());
        return ret;
    }
    
private:
    template<typename T>
    void nextPermutation(vector<T> &vec) {
        
        auto privot = next(vec.rbegin());
        while (privot != vec.rend() && *privot >= *prev(privot)) {
            ++privot;
        }
        
        if(privot != vec.rend()) {
            auto change = find_if(vec.rbegin(), privot, bind1st(less<int>(), *privot));
            swap(*change, *privot);
            reverse(vec.rbegin(), privot);
        } else {
            reverse(vec.begin(), vec.end());
        }
        
    }
};

class Solution2 {
public:
    string findKthPermutaion(int n, int k) {
        string s(n, '0');
        
        for (int i = 0; i <= n; i++) {
            s[i] += i + 1;
        }
        
        string ret = kth_permutation(s, k);
        return ret;
    }
private:
    int fic(int n) {
        int result = 1;
        for (int i = 1; i <= n; i++) {
            result *= i;
        }
        return result;
    }
    
    template <typename Seq>
    Seq kth_permutation(Seq &s, int k) {
        int size = s.size();
        Seq result;
        
        int base = fic(size - 1);
        k--;
        
        for (int i = size - 1; i > 0; i--) {
            auto a = next(s.begin(), k / base);
            result.push_back(*a);
            s.erase(a);
            
            k %= base;
            base /= i;
        }
        
        result.push_back(s[0]);
        return result;
    }
};

int main() {
    Solution2 s;
    string ret = s.findKthPermutaion(5, 3);
    for (auto i : ret) {
        cout << i << " ";
    }
 
}
*/