#include <list>
#include <iostream>

using namespace std;

class Solution
{
public:
    void rotate(list<int>& l, int k){
        size_t k_new = l.size() - k % l.size();
        list<int>::iterator point = l.begin();
        advance(point, k_new - 1);
        list<int>::iterator point_next = next(point);

        list<int>::iterator p = l.begin();
        for (int i = 0; i < k_new - 1; i++) {
            list<int>::iterator old = point;
            point = prev(point);
            l.splice(p, l, old);
        }
        
        copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        
        for (int j = 0; j < l.size() - k_new - 1; j++) {
            list<int>::iterator old = prev(l.end());
            l.splice(point_next, l, old);
        }
        
        l.reverse();
    }
};

/*
int main()
{
    Solution s;
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8};
    s.rotate(l, 4);
    
    copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
}
*/