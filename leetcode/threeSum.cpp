/*
#include <vector>
#include <iostream>

using namespace std;

class Sulotion {
public:
    vector<vector<int>> threeSum(vector<int>& vec) {
        vector<vector<int>> result;
        const int target = 0;
        sort(vec.begin(), vec.end());
        
        if (vec.size() < 3) {
            return result;
        }
        vector<int>::iterator last = vec.end();
        for (auto a = vec.begin(); a < prev(last, 2); a++) {
            auto b = next(a);
            auto c = prev(last);
            while (b < c) {
                if (*a + *b + *c < target) {
                    b++;
                } else if(*a + *b + *c > target) {
                    c--;
                } else {
                    result.push_back({*a, *b, *c});
                    b++;
                    c--;
                }
            }
        }
        
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};


int main() {
    Sulotion s;
    std::vector<int> vec = {1, -1, 0, -2, 3};
    std::vector<vector<int>> result = s.threeSum(vec);
    for (auto i : result) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << endl;
    }
}
*/