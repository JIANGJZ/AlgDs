/*
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int size = matrix.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i; j++) {
                swap(matrix[i][j], matrix[size-j-1][size-i-1]);
            }
        }
        
        for (int i = 0; i < size/2; i++) {
            for (int j = 0; j < size; j++) {
                swap(matrix[i][j], matrix[size-i-1][j]);
            }
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> matrix = { {1, 2, 3, 4},
                                   {5, 6, 7, 8},
                                   {9, 10, 11, 12},
                                   {13, 14, 15, 16}};
    
    s.rotate(matrix);
    
    for (auto i : matrix) {
        for (auto j : i) {
            cout << j << "  ";
        }
        cout << endl;
    }
}
*/