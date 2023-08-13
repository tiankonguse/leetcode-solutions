/*************************************************************************
    > File Name: loud-and-rich.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年02月28日 19:45:13
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
  vector<vector<int>> next;
  vector<int> ans;
  void dfsUpdate(int x, vector<int>& quiet) {
    for (int i = 0; i < next[x].size(); i++) {
      int y = next[x][i];
      if (quiet[ans[y]] > quiet[ans[x]]) {
        ans[y] = ans[x];
        dfsUpdate(y, quiet);
      }
    }
  }
  // person x 比 person y 更有钱
  void addRicher(int x, int y, vector<int>& quiet) {
    next[x].push_back(y);
    if (quiet[ans[y]] > quiet[ans[x]]) {
      ans[y] = ans[x];
      dfsUpdate(y, quiet);
    }
  }

 public:
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    next.clear();
    ans.clear();
    for (int i = 0; i < quiet.size(); i++) {
      ans.push_back(i);
      next.push_back(vector<int>());
    }

    for (int i = 0; i < richer.size(); i++) {
      addRicher(richer[i][0], richer[i][1], quiet);
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
