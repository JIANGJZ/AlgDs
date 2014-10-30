/*
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    void setMatrix(vector<vector<int>>& matrix) {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();
        
        vector<bool> m_flag(m, false);
        vector<bool> n_flag(n, false);
        
        for(int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    m_flag[i] = true;
                    n_flag[j] = true;
                }
            }
        }
 
//        for (int i = 0; i < m; i++) {
//            if (m_flag[i]) {
//                fill(&matrix[i][0], &matrix[i][0] + n, 0);
//            }
//        }
//        
//        for (int j = 0; j < n; j++) {
//            if (n_flag[j]) {
//                for (int i = 0; i < m; i++) {
//                    matrix[i][j] = 0;
//                }
//            }
//        }
 
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (n_flag[j] == true || m_flag[i] == true) {
                    matrix[i][j] = 0;
                }
            }
        }
        
    }
};


int main() {
    Solution s;
    vector<vector<int>> matrix = {{1, 1, 2, 3, 4},
                                  {0, 2, 1, 3, 1},
                                  {3, 1, 4, 5, 6}};
    
    s.setMatrix(matrix);
    
    for (auto i: matrix) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}
*/