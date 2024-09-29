// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  ll countOfSubstrings(const string& s, const int k) {
    int n = s.size();
    const string AEIOU = "aeiou";

    vector<int> posToNum(n + 2);
    unordered_map<int, int> numToPos;
    unordered_set<char> H = {AEIOU.begin(), AEIOU.end()};
    int fuyinNum = 0;
    for (int i = 1; i <= n; i++) {
      if (!H.count(s[i - 1])) {
        fuyinNum++;
      }
      posToNum[i] = fuyinNum;
      if (!numToPos.count(fuyinNum)) {
        numToPos[fuyinNum] = i;
      }
    }
    numToPos[fuyinNum + 1] = n + 1;  // 最后一个标记为辅音

    ll ans = 0;
    unordered_map<char, int> aeiouCount;
    int aeiouNum = 0;
    int r = 1;
    for (int l = 1; l <= n; l++) {
      while (aeiouNum < 5 && r <= n) {
        const char c = s[r - 1];
        if (H.count(c)) {
          aeiouCount[c]++;
          if (aeiouCount[c] == 1) {  // 找到一个元音
            aeiouNum++;
          }
        }
        r++;
      }

      if (aeiouNum < 5) {
        break;  // 没找到，后缀都没答案
      }

      // [l,r) 区间内辅音不超过 k， 后缀辅音不小于 k 才有答案
      if (posToNum[r-1] - posToNum[l - 1] <= k &&
          posToNum[n] - posToNum[l - 1] >= k) {
        int preNum = posToNum[l - 1] + k;
        int minPos = max(numToPos[preNum], r-1);
        int maxPos = numToPos[preNum + 1];
        myprintf("l=%d r=%d preNum=%d minPos=%d maxPos=%d add=%d\n", l, r, preNum, minPos, maxPos, maxPos - minPos);
        ans += maxPos - minPos;
      }

      {
        const char c = s[l - 1];
        if (H.count(c)) {
          aeiouCount[c]--;
          if (aeiouCount[c] == 0) {  // 找到一个元音
            aeiouNum--;
          }
        }
      }
    }
    return ans;
  }
};