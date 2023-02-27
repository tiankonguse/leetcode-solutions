// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumScore(const string& s, const string& t) {
    int tn = t.size();
    int sn = s.size();
    vector<int> pre;
    pre.reserve(tn);

    for (int ti = 0, si = 0; ti < tn && si < sn; ti++, si++) {
      while (si < sn && t[ti] != s[si]) si++;
      if (si == sn) break;
      pre.push_back(si);
    }
    if (pre.size() == tn) return 0;  // 是子序列

    vector<int> suf;
    suf.reserve(tn);
    for (int ti = tn - 1, si = sn - 1; si >= 0 && ti >= 0; ti--, si--) {
      while (si >= 0 && t[ti] != s[si]) si--;
      if (si < 0) break;
      suf.push_back(si);
    }
    std::reverse(suf.begin(), suf.end());

    //     printf("pre: ");
    //     for (auto si : pre) {
    //       printf("%d ", si);
    //     }
    //     printf("\n");

    //     printf("suf: ");
    //     for (auto si : suf) {
    //       printf("%d ", si);
    //     }
    //     printf("\n");

    int ans = tn;
    int rightNum = suf.size();
    ans = min(ans, tn - rightNum);

    int leftNum = pre.size();
    ans = min(ans, tn - leftNum);

    if (pre.size() && suf.size()) {
      for (int ti = 0; ti < pre.size(); ti++) {
        int si = pre[ti];
        leftNum = ti + 1;
        rightNum = suf.end() - lower_bound(suf.begin(), suf.end(), si + 1);
        // printf("ti=%d leftNum = %d rightNum=%d\n", ti, leftNum, rightNum);
        ans = min(ans, tn - leftNum - rightNum);
      }
    }
    return ans;
  }
};