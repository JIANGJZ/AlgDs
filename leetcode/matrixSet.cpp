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

class Solution2 {
public:
    void setMatrix(vector<vector<int>> &matrix) {
        
        bool m_flag = false;
        
        for (int i = 0; i < matrix[0].size(); i++) {
            if (matrix[0][i] == 0) {
                m_flag = true;
                break;
            }
        }
        
        bool n_flag = false;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][0] == 0) {
                n_flag = true;
                break;
            }
        }
        
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[0].size(); j++) {
                if (matrix[0][j] == 0 || matrix[i][0] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        if (n_flag) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
        
        if (m_flag) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[0][j] = 0;
            }
        }
        
    }
};

int main() {
    Solution s;
    Solution2 s2;
    vector<vector<int>> matrix = {{1, 1, 2, 3, 4},
                                  {0, 2, 1, 3, 1},
                                  {3, 1, 4, 5, 6}};
    
    s2.setMatrix(matrix);
    
    for (auto i: matrix) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}
*/