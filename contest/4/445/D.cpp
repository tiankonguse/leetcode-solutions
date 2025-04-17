
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  bool IsZero(const string& s) {
    for (auto c : s) {
      if (c != '0') {
        return false;
      }
    }
    return true;
  };
  // 从 10 进制转化为 B 进制， B 范围 [2, 10]
  // 由于会越界，需要使用 int238 来计算
  string TransToB(string& s, int b) {
    string res = "";
    while (!IsZero(s)) {
      string quotient;
      int pre = 0;
      for (auto c : s) {
        int cur = pre * 10 + (c - '0');
        quotient.push_back('0' + (cur / b));
        pre = cur % b;
      }
      res.push_back('0' + pre);
      s.swap(quotient);
    }
    while (res.size() >= 2 && res.back() == '0') {
      res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
  }
  vector<vector<vector<ll>>> dp;  // dp[pos][state][pre]
  // pos: 当前位数，l: 下界，r: 上界，b: 进制，state: 状态，pre: 前一个字符
  ll Dfs(int pos, const string& l, const string& r, const int& b, int state, char pre = '0') {
    /*
      state
      0: [l[pos], r[pos]]
      1: [l[pos], b-1]
      2: [0, r[pos]]
      3: [0, b-1]
    */
    if (pos < 0) return 1;

    ll& res = dp[pos][state][pre - '0'];
    if (res != -1) return res;
    res = 0;
    if (state == 0) {  // 贴合上下界选择
      for (char c = l[pos]; c <= r[pos]; c++) {
        if (c < pre) continue;  // 不能小于前一个字符
        if (c == l[pos] && c == r[pos]) {
          res = (res + Dfs(pos - 1, l, r, b, 0, c)) % mod;
        } else if (c == l[pos] && c < r[pos]) {
          res = (res + Dfs(pos - 1, l, r, b, 1, c)) % mod;
        } else if (c > l[pos] && c < r[pos]) {
          res = (res + Dfs(pos - 1, l, r, b, 3, c)) % mod;
        } else {  // if(c > l[pos] && c == r[pos])
          res = (res + Dfs(pos - 1, l, r, b, 2, c)) % mod;
        }
      }
    } else if (state == 1) {  // 贴合下界选择
      for (char c = l[pos]; c < '0' + b; c++) {
        if (c < pre) continue;
        if (c == l[pos]) {
          res = (res + Dfs(pos - 1, l, r, b, 1, c)) % mod;
        } else {
          res = (res + Dfs(pos - 1, l, r, b, 3, c)) % mod;
        }
      }
    } else if (state == 2) {  // 贴合上界选择
      for (char c = '0'; c <= r[pos]; c++) {
        if (c < pre) continue;
        if (c == r[pos]) {
          res = (res + Dfs(pos - 1, l, r, b, 2, c)) % mod;
        } else {
          res = (res + Dfs(pos - 1, l, r, b, 3, c)) % mod;
        }
      }
    } else {  // if (state == 3) 任意选择
      for (char c = '0'; c < '0' + b; c++) {
        if (c < pre) continue;
        res = (res + Dfs(pos - 1, l, r, b, 3, c)) % mod;
      }
    }

    return res;
  }

 public:
  ll countNumbers(string l, string r, int b) {
    // 第一步：转化为 B 进制
    l = TransToB(l, b);
    r = TransToB(r, b);
    // 第二步：对齐高位，补 0
    int len = max(l.size(), r.size()) + 1;
    std::reverse(l.begin(), l.end());
    std::reverse(r.begin(), r.end());
    l.resize(len, '0');
    r.resize(len, '0');
    // std::reverse(l.begin(), l.end());
    // std::reverse(r.begin(), r.end());
    // MyPrintf("l = %s, r = %s\n", l.c_str(), r.c_str());
    // 第三步：DFA 计算数位DP
    dp.resize(len, vector<vector<ll>>(4, vector<ll>(b, -1)));
    return Dfs(len - 1, l, r, b, 0);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(string l, string r, int b, const ll& ans) {  //
  TEST_SMP3(Solution, countNumbers, ans, l, r, b);
}

int main() {
  string l = "23";
  string r = "28";
  int b = 8;
  Test(l, r, b, 3);

  l = "2";
  r = "7";
  b = 2;
  Test(l, r, b, 2);
  return 0;
}

#endif