#include <iostream>
using namespace std;

class Sulotion {
public:
    double findMedia(int A[], int n, int B[], int m) {
        int merge_length = n + m;
        if (merge_length & 0x01) {
            return find_kth_1(A, n, B, m, (merge_length/2) +1);
        } else {
            return (find_kth_1(A, n, B, m, merge_length/2) +
                    find_kth_1(A, n, B, m, (merge_length/2) + 1))/2.0;
        }
    }
    
private:
    int find_kth_1(int A[], int m, int B[], int n, int k) {
        if (m > n) {
            return find_kth_1(B, n, A, m, k);
        }
        
        if (k == 1) {
            return min(A[0], B[0]);
        }
        
        if (m == 0) {
            return B[k - 1];
        }
        
        int ia = min(k / 2, m);
        int ib = k - ia;
        if (A[ia - 1] < B[ib -1]) {
            return find_kth_1(A + ia, m - ia, B, n, k - ia);
        } else if(A[ia - 1] > B[ib - 1]){
            return find_kth_1(A, m, B + ib, n, k - ib);
        } else {
            return A[ia - 1];
        }
    }
    
    int find_kth_2(int A[], int n, int B[], int m, int k) {
        int count_both = 0;
        int count_A = 0;
        int count_B = 0;
        
        while (count_both < k) {
            if (A[count_A] < B[count_B]) {
                count_A++;
                count_both++;
            } else {
                count_B++;
                count_both++;
            }
        }
        return A[count_A - 1] > B[count_B - 1] ? A[count_A - 1] : B[count_B - 1];
    }
    
};

int main() {
    int A[5] = {1, 2, 6, 7, 8};
    int B[3] = {1, 2, 5};
    Sulotion s;
    cout << s.findMedia(A, 5, B, 3) << endl;
}