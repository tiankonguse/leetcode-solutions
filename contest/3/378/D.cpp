// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int printfEmpty(const char*, ...) { return 0; }

// #define myPrintf printf
#define myPrintf printfEmpty

typedef long long ll;
struct Stat {
  vector<vector<int>> preStat;
  Stat(int n) { preStat.resize(n + 3, vector<int>(26, 0)); }
};
struct Range {
  int l = 0;
  int r = 0;
  Range(const int L, const int R) {
    l = L;
    r = R;
  }
  void Output() { myPrintf("l=%d r=%d\n", l, r); }
};
class Solution {
 public:
  vector<bool> canMakePalindromeQueries(const string& s,
                                        vector<vector<int>>& queries) {
    const int n = s.length();
    const int nn = n / 2;
    vector<int> preCmp(nn + 3, -1);
    preCmp[0] = -1;
    for (int i = 1; i <= nn; i++) {
      if (s[i - 1] == s[n - i]) {
        preCmp[i] = preCmp[i - 1];
      } else {
        preCmp[i] = i;
      }
    }
    vector<int> subCmp(nn + 3, -1);
    subCmp[nn + 1] = -1;
    for (int i = nn; i >= 1; i--) {
      if (s[i - 1] == s[n - i]) {
        subCmp[i] = subCmp[i + 1];
      } else {
        subCmp[i] = i;
      }
    }

    Stat stat1(nn), stat2(nn);
    vector<vector<int>>& preStat1 = stat1.preStat;
    vector<vector<int>>& preStat2 = stat2.preStat;
    for (int i = 1; i <= nn; i++) {
      int val1 = s[i - 1] - 'a';
      preStat1[i] = preStat1[i - 1];
      preStat1[i][val1]++;

      int val2 = s[n - i] - 'a';
      preStat2[i] = preStat2[i - 1];
      preStat2[i][val2]++;
    }

    auto Check = [&](const Range& range1, const Stat& stat1,
                     const Stat& stat2) -> bool {
      int l = range1.l;
      int r = range1.r;

      for (int i = 0; i < 26; i++) {
        int num1 = stat1.preStat[r][i] - stat1.preStat[l - 1][i];
        int num2 = stat2.preStat[r][i] - stat2.preStat[l - 1][i];
        if (num1 != num2) {
          return false;  // 有字符个数不一致，无法形成回文
        }
      }

      return true;
    };

    auto Solver = [&](const Range& range1, const Range& range2,
                      const Stat& stat1,
                      const Stat& stat2) -> bool {  //
      int minLeft = min(range1.l, range2.l);
      int maxRight = max(range1.r, range2.r);

      if (preCmp[minLeft - 1] != -1) {
        myPrintf("left no ans, minLeft=%d\n", minLeft);
        return false;  // 左边不对称
      }
      if (subCmp[maxRight + 1] != -1) {
        myPrintf("right no ans, maxRight=%d\n", maxRight);
        return false;  // 右边不对称
      }

      if (range1.r < range2.l) {  // 没有交集
        myPrintf("no cross\n");
        if (preCmp[range2.l - 1] > range1.r) {
          myPrintf("mid no ans, midLeft=%d minRight=%d\n", range1.r + 1,
                   range2.l - 1);
          return false;  // 中间不对称
        }
        if (!Check(range1, stat1, stat2)) {
          myPrintf("left half no ans, L=%d R=%d\n", range1.l, range1.r);
          return false;  // 左半部不一致
        }
        if (!Check(range2, stat2, stat1)) {
          myPrintf("right half no ans, L=%d R=%d\n", range2.l, range2.r);
          return false;  // 右半部不一致
        }
        return true;
      }

      // 有交集
      vector<int> count1(26, 0);
      vector<int> count2(26, 0);

      for (int i = 0; i < 26; i++) {
        count1[i] = stat1.preStat[maxRight][i] - stat1.preStat[minLeft - 1][i];
        count2[i] = stat2.preStat[maxRight][i] - stat2.preStat[minLeft - 1][i];
      }

      int l1 = range1.l;
      int r1 = range1.r;
      int l2 = range2.l;
      int r2 = range2.r;
      // 步骤1：
      if (l1 < l2) {  // 左半部对齐
        myPrintf("left more, try check\n");
        for (int i = 0; i < 26; i++) {  // [l1, l2-1]
          const int num2 = stat2.preStat[l2 - 1][i] - stat2.preStat[l1 - 1][i];
          count1[i] -= num2;
          count2[i] -= num2;
          if (count1[i] < 0) {
            myPrintf("left more, count1  check fasle, char=%c\n", 'a' + i);
            return false;
          }
          if (count2[i] < 0) {
            myPrintf("left more, count2 check fasle, char=%c\n", 'a' + i);
            return false;
          }
        }
        l1 = l2;
      }

      if (r1 < r2) {  //右半部对齐
        myPrintf("right more, up short, try check， r1=%d r2=%d\n", r1, r2);
        for (int i = 0; i < 26; i++) {  // [r1+1, r2]
          const int num1 = stat1.preStat[r2][i] - stat1.preStat[r1][i];
          count1[i] -= num1;
          count2[i] -= num1;
          if (count1[i] < 0) {
            myPrintf("right more, up short, count1  check fasle, char=%c\n",
                     'a' + i);
            return false;
          }
          if (count2[i] < 0) {
            myPrintf("right more, up short, count2 check fasle, char=%c\n",
                     'a' + i);
            return false;
          }
        }
        r2 = r1;
      } else if (r1 > r2) {
        myPrintf("right more, down short, try check\n");
        for (int i = 0; i < 26; i++) {  // [r2+1, r1]
          const int num2 = stat2.preStat[r1][i] - stat2.preStat[r2][i];
          count1[i] -= num2;
          count2[i] -= num2;
          if (count1[i] < 0) {
            myPrintf("right more, down short, count1  check fasle, char=%c\n",
                     'a' + i);
            return false;
          }
          if (count2[i] < 0) {
            myPrintf("right more, down short, count2 check fasle, char=%c\n",
                     'a' + i);
            return false;
          }
        }
        r1 = r2;
      }

      //中间对齐
      return count1 == count2;
    };

    if (preStat1[nn] != preStat2[nn]) {
      myPrintf("s=%s all no ans\n", s.c_str());
      return vector<bool>(queries.size(), false);
    }
    vector<bool> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      Range range1(q[0] + 1, q[1] + 1);
      Range range2(n - q[3], n - q[2]);
      myPrintf("s=%s\n", s.c_str());
      range1.Output();
      range2.Output();
      if (range1.l <= range2.l) {
        bool tmp = Solver(range1, range2, stat1, stat2);
        ans.push_back(tmp);
      } else {
        myPrintf("swap left and right\n");
        bool tmp = Solver(range2, range1, stat2, stat1);
        ans.push_back(tmp);
      }
      myPrintf("ans=%d\n", bool(ans.back()));
    }
    return ans;
  }
};