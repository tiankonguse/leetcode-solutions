
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
  int n;
  int SolverOne(const string& s) {
    int ans = 0;

    char pre = s[0];
    int cnt = 0;
    for (auto c : s) {
      if (c != pre) {
        pre = c;
        cnt = 0;
      }
      cnt++;
      ans = max(ans, cnt);
    }
    MyPrintf("Solver1 ans=%d\n", ans);
    return ans;
  }
  int SolverThree(const string& s) {
    int ans = 0;
    map<pair<int, int>, int> mp;  // {a,b}, cnt
    mp[{0, 0}] = 0;
    pair<int, int> cnt = {0, 0};  // a,b
    for (int i = 1; i <= n; i++) {
      char c = s[i - 1];
      if (c == 'a') {
        cnt.first++;
      } else if (c == 'b') {
        cnt.second++;
      } else {
        cnt.first--;
        cnt.second--;
      }
      if (mp.count(cnt)) {
        ans = max(ans, i - mp[cnt]);
      } else {
        mp[cnt] = i;  // 记录最早的位置
      }
    }
    MyPrintf("Solver3 ans=%d\n", ans);
    return ans;
  }
  int SolverTwo(const string& s) {
    int ans = 0;
    unordered_map<int, int> mp;  // diff, idx
    pair<int, int> rangeFlag = {0, 0};
    int startOffset = 0;
    int diff = 0;  // a-b
    char pre = s[0] == 'a' ? 'b' : 'a';
    int lastPre = 0;
    char now = s[0];
    int lastNow = 1;
    auto Update = [&](int i) {
      if (rangeFlag.first <= diff && diff <= rangeFlag.second) {
        if (diff <= 0) {
          const int offset = startOffset - diff;
          ans = max(ans, i - offset);
        } else {
          const int offset = startOffset + diff;
          ans = max(ans, i - offset);
        }
      } else if (mp.count(diff)) {
        ans = max(ans, i - mp[diff]);
      } else {
        mp[diff] = i;
      }
    };
    for (int i = 1; i <= n; i++) {
      char c = s[i - 1];
      if (c != now && c != pre) {
        if (pre == s[i - 2]) { // 相邻的时 pre
          int preFirst = lastNow + 1;
          int preLast = lastPre;
          int preNum = lastPre - preFirst + 1;
          startOffset = lastNow;
          rangeFlag = {-preNum, 0};
          now = c;
          diff = -preNum;
        } else { // 相邻的是 now
          int nowFirst = lastPre + 1;
          int nowLast = lastNow;
          int nowNum = lastNow - nowFirst + 1;
          startOffset = lastPre;
          rangeFlag = {0, nowNum};
          pre = c;
          lastPre = i;
          diff = nowNum;
        }
        mp.clear();
      }

      if (c == now) {
        diff++;
        lastNow = i;
      } else if (c == pre) {
        diff--;
        lastPre = i;
      }
      Update(i);
    }
    MyPrintf("Solver2 ans=%d\n", ans);
    return ans;
  }

 public:
  int longestBalanced(const string& s) {
    n = s.size();
    int ans = 1;
    // 字符为 1 个的场景
    ans = max(ans, SolverOne(s));
    // 字符为 3 个的场景
    ans = max(ans, SolverThree(s));
    // 字符为 2 个的场景
    ans = max(ans, SolverTwo(s));
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