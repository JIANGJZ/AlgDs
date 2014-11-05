/*
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int canComplteCircuit(vector<int>& gas, vector<int>& cost) {
        int i, j;
        for (i = 0; i < gas.size(); i++) {
            int sum = 0;
            for (j = 0; j < gas.size(); j++) {
                sum += (gas[(i+j)%gas.size()] - cost[(i+j)%gas.size()]);
                if (sum < 0) {
                    break;
                }
            }
            if (j == gas.size()) {
                break;
            }
        }
        
        if (i == gas.size()) {
            return -1;
        } else {
            return i;
        }
    }
};

class Solution2
{
public:
    int canComplteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0;
        int j = -1;
        for (int i = 0, sum = 0; i < gas.size(); i++) {
            sum += gas[i] - cost[i];
            total += gas[i] - cost[i];
            if (sum < 0) {
                j = i;
                sum = 0;
            }
        }
        
        return total >= 0 ? j+1 : -1;
    }
};

int main() {
    Solution s;
    Solution2 s2;
    vector<int> gas = {1, 2, 3, 4, 5, 6};
    vector<int> cost = {1, 3, 4, 5, 1, 1};
    cout << s2.canComplteCircuit(gas, cost);
}
*/