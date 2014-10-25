/*
#include <vector>
#include <unordered_map>
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
    vector<vector<int>> fourSum(vector<int>& vec, int target) {
        vector<vector<int>> result;
        if (vec.size() < 4) {
            return result;
        }
        
        sort(vec.begin(), vec.end());
        
        unordered_map<int, vector<pair<int, int>>> cache;
        for (auto a = 0; a < vec.size(); a++) {
            for (auto b = a + 1; b < vec.size(); b++) {
                cache[vec[a] + vec[b]].push_back(pair<int, int>(a, b));
            }
        }
        
        for (auto c = 0; c < vec.size(); c++) {
            for (auto d = c + 1; d < vec.size(); d++) {
                
                int key = target - vec[c] - vec[d];
                
                if (cache.find(key) == cache.end()) {
                    continue;
                }
                
                auto& temp_vec = cache[key];
                for (auto k = 0; k < temp_vec.size(); k++) {
                    if (c <= temp_vec[k].second) {
                        continue;
                    }
                    result.push_back({vec[temp_vec[k].first], vec[temp_vec[k].second], vec[c], vec[d]});
                }
            }
        }
        
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        
        return result;
    }
};

class Solution3 {
public:
    vector<vector<int>> fourSum(vector<int> vec, int target) {
        vector<vector<int>> result;
        
        if (vec.size() < 4) {
            return result;
        }
        
        sort(vec.begin(), vec.end());
        
        unordered_multimap<int, pair<int, int>> cache;
        for (auto a = 0; a < vec.size(); a++) {
            for (auto b = a + 1; b < vec.size(); b++) {
                cache.insert(make_pair(vec[a] + vec[b], make_pair(a, b)));
            }
        }
        
        for (auto i = cache.begin(); i != cache.end(); i++) {
            int x = target - i->first;
            auto range = cache.equal_range(x);
            
            for (auto j = range.first; j != range.second; j++) {
                auto a = i->second.first;
                auto b = i->second.second;
                auto c = j->second.first;
                auto d = j->second.second;
                if (a != c && a != d && b != c && b!= d) {
                    vector<int> temp = {vec[a], vec[b], vec[c], vec[d]};
                    sort(temp.begin(), temp.end());
                    result.push_back(temp);
                }
            }
        }
        
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};

class Solution4 {
public:
    vector<vector<int>> fourSum(vector<int> vec, int target) {
        vector<vector<int>> result;
        if (vec.size() < 4) {
            return result;
        }
        
        sort(vec.begin(), vec.end());
        
        for (auto a = vec.begin(); a < prev(vec.end(), 3); a = upper_bound(a, prev(vec.end(), 3), *a)) {
            for (auto b = a + 1; b < prev(vec.end(), 2); b = upper_bound(b, prev(vec.end(), 2), *b)) {
                auto c = next(b);
                auto d = prev(vec.end());
                while (c < d) {
                    if (*a + *b + *d + *c < target) {
                        c = upper_bound(c, d, *c);
                    } else if(*a + *b + *c + *d > target) {
                        d = prev(lower_bound(c, d, *d));
                    } else {
                        result.push_back({*a, *b, *c, *d});
                        c = upper_bound(c, d, *c);
                        d = prev(lower_bound(c, d, *d));
                    }
                }
            }
        }
        
        return result;
    }
};

int main() {
    Solution4 s4;
    vector<int> vec = {1, -1, 3, 2, 4, 5, 7, 0, -2};
    vector<vector<int>> result = s4.fourSum(vec, 0);
    for(auto i : result) {
        for(auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}
*/