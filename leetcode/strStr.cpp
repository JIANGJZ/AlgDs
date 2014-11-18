#include <string.h>
#include <iostream>

using namespace std;

class Solution
{
public:
    char* strStr(const char* text, const char* pattern) {
        if (text == nullptr || pattern == nullptr) {
            return nullptr;
        }
        
        size_t len_text = strlen(text);
        size_t len_patten = strlen(pattern);
        auto i = 0;
        auto j = 0;
        for (i = 0; i < len_text - len_patten; i++) {
            for (j = 0; j < len_patten; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            
            if (j >= len_patten) {
                return (char*)(text+i);
            }
            
        }
        
        return nullptr;
        
    }
};

/*
int main()
{
    Solution s;
    const char* text = "hello world";
    const char* patten = "llo";
    cout << s.strStr(text, patten);
}
*/