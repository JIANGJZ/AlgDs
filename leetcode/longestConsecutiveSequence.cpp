/*
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
using namespace std;

class Sulotion {
public:
    int longestConsecutive(const std::vector<int> vec) {
        unordered_map<int, bool> used;
        for (auto i : vec) {
            used[i] = false;
        }
        
        int longest = 0;
        for (auto i : vec) {
            if (used[i]) {
                continue;
            }
            int length = 1;
            used[i] = true;
            for (int j = i + 1; used.find(j) != used.end(); j++) {
                used[j] = true;
                length++;
            }
            
            for (int j = i - 1; used.find(j) != used.end(); j++) {
                used[j] = true;
                length++;
            }
            longest = max(longest, length);
            
        }
        
        return longest;
    }
};

class Sulotion2 {
public:
    int longestConsecutive(const std::vector<int> &vec) {
        unordered_map<int, int> map;
        size_t size = vec.size();
        int l = 1;
        for (int i = 0; i < size; i++) {
            if (map.find(vec[i]) != map.end()) {
                continue;
            }
            map[vec[i]] = 1;
            if (map.find(vec[i] - 1) != map.end()) {
                l = max(l, mergeCluster(map, vec[i] - 1, vec[i]));
            }
            
            if (map.find(vec[i] + 1) != map.end()) {
                l = max(l, mergeCluster(map, vec[i], vec[i] + 1));
            }
        }
        return size == 0 ? 0 : l;
    }
private:
    int mergeCluster(unordered_map<int, int> &map, int left, int right) {
        int upper = right + map[right] - 1;
        int lower = left - map[left] + 1;
        int length = upper - lower + 1;
        map[upper] = length;
        map[lower] = length;
        return length;
    }
};


int main() {
    Sulotion2 s;
    std::vector<int> vec = {1, 3, 51, 35, 2, 4};
    cout << s.longestConsecutive(vec) << endl;
    
}
 */
