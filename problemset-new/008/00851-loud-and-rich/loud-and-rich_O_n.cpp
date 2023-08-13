/*************************************************************************
    > File Name: loud-and-rich_O_n.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年02月28日 21:53:03
 ************************************************************************/

#include <time.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "../../include/base.h"
using namespace std;

#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;

class Solution {
  vector<vector<int>> pre;
  vector<int> ans;
  void dfs(int x, vector<int>& quiet) {
    if (ans[x] != -1) {
      return;
    }
    ans[x] = x;
    for (int i = 0; i < pre[x].size(); i++) {
      int y = pre[x][i];
      dfs(y, quiet);
      if (quiet[ans[y]] < quiet[ans[x]]) {
        ans[x] = ans[y];
      }
    }
  }

 public:
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    pre.clear();
    ans.clear();
    ans.resize(quiet.size(), -1);
    pre.resize(quiet.size());

    //先构造图
    for (int i = 0; i < richer.size(); i++) {
      pre[richer[i][1]].push_back(richer[i][0]);
    }

    // dfs 查找
    for (int i = 0; i < quiet.size(); i++) {
      dfs(i, quiet);
    }

    return ans;
  }
};

void test(vector<vector<int>>& richer, vector<int>& quiet,
          vector<int>& expectAns) {
  Solution work;
  vector<int> ans;
  ans = work.loudAndRich(richer, quiet);
  output("richer", richer);
  output("quiet", quiet);
  output("ans", ans);
  output("expectAns", expectAns);
}

int main() {
  vector<vector<int>> richer;
  vector<int> quiet;
  vector<int> expectAns;

  richer = {{1, 0}, {2, 1}, {3, 1}, {3, 7}, {4, 3}, {5, 3}, {6, 3}};
  quiet = {3, 2, 5, 4, 6, 1, 7, 0};
  expectAns = {5, 5, 2, 5, 4, 5, 6, 7};
  test(richer, quiet, expectAns);

  return 0;
}
