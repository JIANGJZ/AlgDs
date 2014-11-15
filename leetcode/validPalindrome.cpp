#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    bool isPalindrome(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        
        auto left = s.begin();
        auto right = prev(s.end());
        
        while (left < right) {
            if (!isalnum(*left)) {
                left++;
            }
            else if (!isalnum(*right)) {
                right--;
            }
            else if (*left == * right) {
                left++;
                right--;
            }
            else{
                return false;
            }
            
        }
        return true;
    }
};

/*
int main()
{
    Solution s;
    string str = "race the other";
    cout << s.isPalindrome(str) << endl;
    
    string str2 = "A man, a plan, a canal: Panama";
    cout << s.isPalindrome(str2);
}
*/