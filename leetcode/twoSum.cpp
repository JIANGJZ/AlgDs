/*
#include <vector>
#include <unordered_map>
#include <iostream>

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int> &vec, int target) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < vec.size(); i++) {
            map[vec[i]] = i;
        }
        std::vector<int> result;
        for (int i = 0; i < vec.size(); i++) {
            const int gap = target - vec[i];
            if (map.find(gap) != map.end()) {
                result.push_back(i + 1);
                result.push_back(map[gap] + 1);
                break;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    std::vector<int> vec = {1, 2, 7, 10, 8, 9};
    std::vector<int> result = s.twoSum(vec, 15);
    for(auto i : result) {
        std::cout << i << std::endl;
    }
}
 */
