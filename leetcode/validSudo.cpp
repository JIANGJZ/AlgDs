#include <vector>
#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isValidSudo(vector<vector<char>>& board) {
        bitset<9> used;
        for (auto i : board) {
            used.reset();
            for (auto j : i) {
                if (!check(j, used)) {
                    return false;
                }
            }
        }
        
        for (int i = 0; i < board.size(); i++) {
            used.reset();
            for (int j = 0; j < board.size(); j++) {
                if (!check(board[j][i], used)) {
                    return false;
                }
            }
        }
        
        int unit = sqrt(board.size());
        for (int r = 0; r < unit; r++) {
            for (int c = 0; c < unit; c++) {
                used.reset();
                
                for (int i = r*unit; i < r*unit + unit; i++) {
                    for (int j = c*unit; j < c*unit; j++) {
                        if (!check(board[i][j], used)) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    
private:
    bool check(char c, bitset<9> &used) {
        if (c == '.') {
            return true;
        }
        if (used.test(c - '1') == true) {
            return false;
        }else{
            used.set(c - '1');
            return true;
        }
    }
};

int main() {
    Solution s;
    vector<vector<char>> board= {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    
    cout << s.isValidSudo(board);
}