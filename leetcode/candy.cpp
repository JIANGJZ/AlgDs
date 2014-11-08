#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

using namespace std;

class Solution1
{
public:
    int candy(vector<int>& rating) {
        const int s = (int)rating.size();
        
        vector<int> increment(s);
        
        int inc = 1;
        for (int i = 1; i < s; i++) {
            if (rating[i] > rating[i-1]) {
                increment[i] = max(inc++, increment[i]);
            } else {
                inc = 1;
            }
        }
        
        inc = 1;
        for (int i = s - 2; i >= 0; i--) {
            if (rating[i] > rating[i+1]) {
                increment[i] = max(inc++, increment[i]);
            } else {
                inc = 1;
            }
        }
        
        return  accumulate(&increment[0], &increment[0]+s, s);
    }
};

class Solution2
{
public:
    int candy(vector<int>& rating) {
        vector<int> f(rating.size());
        
        int sum = 0;
        for (int i = 0; i < rating.size(); i++) {
            sum += solve(rating, f, i);
        }
        return sum;
    }
    
private:
    int solve(const vector<int>& ratings, vector<int>& f, int i) {
        if (f[i] == 0) {
            f[i] = 1;
            if (i > 0 && ratings[i] > ratings[i-1]) {
                f[i] = max(f[i], solve(ratings, f, i-1)+1);
            }
            if (i < ratings.size() - 1 && ratings[i] > ratings[i+1]) {
                f[i] = max(f[i], solve(ratings, f, i+1)+1);
            }
        }
        return f[i];
    }
    
};


/*
int main()
{
    Solution1 s;
    Solution2 s2;
    vector<int> rating = {1, 2, 3, 1, 2, 3};
    cout << s.candy(rating) << endl;
    cout << s2.candy(rating) << endl;
}
*/