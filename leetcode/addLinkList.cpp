#include <iostream>
#include <list>

using namespace std;

class Solution
{
public:
    void addLinkList(list<int>& L1, list<int>& L2, list<int> &result) {
        int carry = 0;
        list<int>::iterator L1_iter = L1.begin();
        list<int>::iterator L2_iter = L2.begin();
        
        for (; L1_iter != L1.end() && L2_iter != L2.end(); L1_iter++, L2_iter++) {
            int value = (*L1_iter + *L2_iter + carry) % 10;
            result.push_back(value);
            carry = (*L1_iter + *L2_iter + carry) / 10;
        }
        
        if (L1_iter == L1.end()) {
            while (L2_iter != L2.end()) {
                int value = (carry + *L2_iter) % 10;
                result.push_back(value);
                carry = (carry + *L2_iter) / 10;
                L2_iter++;
            }
        } else {
            while (L1_iter != L1.end()) {
                int value = (carry + *L1_iter) % 10;
                result.push_back(value);
                carry = (carry + *L1_iter) / 10;
                L1_iter++;
            }
        }
        
        if(carry != 0) {
            result.push_back(carry);
        }
    }
};


class Solution2 {
public:
    void addLinkList(list<int>& L1, list<int>& L2, list<int>& result) {
        int carry = 0;
        list<int>::iterator L1_iter = L1.begin();
        list<int>::iterator L2_iter = L2.begin();
        
        for(; L1_iter != L1.end() || L2_iter != L2.end();
            ((L1_iter == L1.end()) ? L1_iter : ++L1_iter),
            ((L2_iter == L2.end()) ? L2_iter : ++L2_iter)) {
            int value1 = ( L1_iter == L1.end() ? 0 : *L1_iter);
            int value2 = ( L2_iter == L2.end() ? 0 : *L2_iter);
            int value = (carry + value1 + value2) % 10;
            result.push_back(value);
            carry = (carry + value1 + value2) / 10;
        }
        
        if (carry > 0) {
            result.push_back(carry);
        }
    }
};

/*
int main()
{
    Solution s;
    list<int> L1 = {2, 4, 5};
    list<int> L2 = {5, 6, 4};
    list<int> result;
    s.addLinkList(L1, L2, result);
    ostream_iterator<int> out(cout, " ");
    copy(result.begin(), result.end(), out);
    
    Solution2 s2;
    list<int> result2;
    list<int> L3 = {1, 2, 5};
    list<int> L4 = {3, 4, 5};
    s2.addLinkList(L3, L4, result2);
    ostream_iterator<int> out2(cout, " ");
    copy(result2.begin(), result2.end(), out2);
    
    return 0;
}
*/