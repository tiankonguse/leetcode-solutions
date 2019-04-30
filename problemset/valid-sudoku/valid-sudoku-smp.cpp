/*************************************************************************
    > File Name: valid-sudoku-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 01:00:34 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int indexSet(int k, int i, int j) {
        if(k == 0) {
            return 10 + i;
        } else if(k == 1) {
            return 20 + j;
        } else {
            return (i/3)*3 + (j/3);
        }
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        map<int, set<char> > m;
        for(int i=0; i<board.size(); i++) {
            for(int j=0; j<board[i].size(); j++) {
                const char c = board[i][j];
                if(c == '.') {
                    continue;
                }
                for(int k=0; k<3; k++) {
                    auto& s = m[indexSet(k, i, j)];
                    if(s.find(c) != s.end()) {
                        return false;
                    } else {
                        s.insert(c);
                    }
                }
            }
        }
        return true;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;


    first = 1;
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
*/
int main() {
#define CLASS Solution
#define FUNCTION isValidSudoku

    vector<vector<char>> first;
    int second;
    bool expectAns;

    first = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    second = 1;
    expectAns = true;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    second = 1;
    expectAns = false;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    return 0;
}
