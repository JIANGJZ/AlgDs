#include <iostream>
#include <string.h>

using namespace std;

void reverseString(char* pBegin, char* pEnd) {
    if (pBegin == NULL || pEnd == NULL) {
        return;
    }
    
    while (pBegin < pEnd) {
        char temp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = temp;
        
        pBegin++;
        pEnd--;
    }
}

char* reverseSentence(char* pSentence) {
    if (pSentence == NULL) {
        return NULL;
    }
    
    char* pBegin = pSentence;
    
    char* pEnd = pSentence;
    while (*pEnd != '\0') {
        pEnd++;
    }
    pEnd--;
    
    reverseString(pBegin, pEnd);
    
    pBegin = pEnd = pSentence;
    while (*pBegin != '\0') {
        if (*pEnd == ' ' || *pEnd == '\0') {
            reverseString(pBegin, pEnd - 1);
            pEnd++;
            pBegin = pEnd;
        }
        else{
            pEnd++;
        }
    }
    
    return pSentence;
    
}

char* leftRotateString(char* pStr, int n) {
    if (pStr == NULL) {
        return NULL;
    }
    
    char* pFirstStart = pStr;
    char* pFirstEnd = pStr + n - 1;
    char* pSecondStart = pStr + n;
    char* pSecondEnd = pStr + strlen(pStr) - 1;
    
    reverseString(pFirstStart, pFirstEnd);
    reverseString(pSecondStart, pSecondEnd);
    reverseString(pFirstStart, pSecondEnd);
    
    return pStr;
}

/*
int main() {
    char* sentence = new char[100];
    strcpy(sentence, "hellohello");
    
    //reverseSentence(sentence);
    
    leftRotateString(sentence, 4);
    
    cout << "reverse result: " << sentence << endl;
    
}
 */
