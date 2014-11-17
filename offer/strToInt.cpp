enum Status {
    kValid = 0,
    kInvalid
};

int g_Status = kValid;

long long strToIntCore(const char* digit, bool minus) {
    long long num = 0;
    while (digit != '\0') {
        if (*digit >= '0' && *digit <= '9') {
            int flag = minus ? -1 : 1;
            num = num * 10 + flag * (*digit  - '0');
            
            if ((!minus && num > 0x7FFFFFFF) || (minus && num < (signed int)0x80000000)) {
                num = 0;
                break;
            }
        }
        else {
            num = 0;
            break;
        }
            
    }
    
    if (*digit == '\0') {
        g_Status = kValid;
    }
    
    return num;
}

int strToInt(const char* str) {
    g_Status = kInvalid;
    
    long long num = 0;
    
    if(str != nullptr && str != '\0') {
        
        bool minus = false;
        
        if (*str == '+') {
            str++;
        }
        else if (*str == '-') {
            str++;
            minus = true;
        }
        
        if (*str != '\0') {
            num = strToIntCore(str, minus);
        }
        
    }
    
    return (int)num;
    
}