
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int countBattleships(vector<vector<char>>& board) {
    int n = board.size();
    int m = board.front().size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == '.') continue;
        if (i != 0 && board[i - 1][j] == 'X') continue;
        if (j != 0 && board[i][j - 1] == 'X') continue;
        ans++;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<char>>& board, const int& ans) {
  TEST_SMP1(Solution, countBattleships, ans, board);
}

int main() {
  vector<vector<char>> board = {{'X', '.', '.', 'X'},  //
                                {'.', '.', '.', 'X'},  //
                                {'.', '.', '.', 'X'}};
  Test(board, 2);

  board = {{'.'}};
  Test(board, 0);
  return 0;
}

#endif