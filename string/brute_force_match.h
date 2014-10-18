#ifndef AlgDs_brute_force_match_h
#define AlgDs_brute_force_match_h
#include <cstring>

int brute_force_match1(char const* pattern, char const* str) {
    size_t n = strlen(pattern);
    int i = 0;
    size_t m = strlen(str);
    int j = 0;
    while (j < m && i < n) {
        if (pattern[i] == str[i]) {
            i++;
            j++;
        }else{
            i -= j -1;
            j = 0;
        }
    }
    return i - j;
}

int brute_force_match2(char const* pattern, char const* str) {
    size_t m = strlen(pattern);
    size_t n = strlen(str);
    int i = 0;
    int j = 0;
    for (i = 0; i < (n - m + 1); i++) {
        for (j = 0; j < m; j++) {
            if (str[i + j] != pattern[j]) {
                break;
            }
        }
        if (m <= j) {
            break;
        }
    }
    return i;
}
#endif
