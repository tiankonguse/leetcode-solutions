
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

typedef long long ll;
class Solution {
public:
    int minimumOR(vector<vector<int>>& grid) {
        int n = grid.size();
        int ans = 0;
        const int MaxBit = 20; 
        for (int bit = MaxBit-1; bit >= 0; bit--) {
            int foundNum = 0;
            for (int ni= 0; ni < n; ni++) {
              int m = grid[ni].size();
              for (int mi = 0; mi < m; mi++) {
                  if ((grid[ni][mi] & (1 << bit)) == 0) {
                      foundNum++;
                      break;
                  }
              }
            }
            if (foundNum == n) {
              for (int ni= 0; ni < n; ni++) {
                int m = grid[ni].size();
                for (int mi = 0; mi < m; mi++) {
                    if ((grid[ni][mi] & (1 << bit)) != 0) {
                        swap(grid[ni][mi], grid[ni][m-1]);
                        grid[ni].pop_back();
                        m--;
                        mi--;
                    }
                }
              }
            } else {
                ans |= (1 << bit);
            }
        }
        return ans;
    }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif