
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
/*
0 zero  => z
2 two   => w
6 six   => x
8 eight => g
7 seven => s
3 three => h
4 four  => r
1 one   => o
5 five  => f
9 nine  => i
*/
const vector<string> nums = {"zero", "one", "two",   "three", "four",
                             "five", "six", "seven", "eight", "nine"};
const vector<pair<char, int>> base = {  //
    {'z', 0},                           //
    {'w', 2},                           //
    {'x', 6},                           //
    {'g', 8},                           //
    {'s', 7},                           //
    {'h', 3},                           //
    {'r', 4},                           //
    {'o', 1},                           //
    {'f', 5},                           //
    {'i', 9}};
class Solution {
 public:
  string originalDigits(const string& s) {
    vector<int> stat(26, 0);
    for (auto c : s) {
      stat[c - 'a']++;
    }
    string ans;
    for (const auto& [c, v] : base) {
      while (stat[c - 'a'] > 0) {
        ans.push_back('0' + v);
        for (auto a : nums[v]) {
          stat[a - 'a']--;
        }
      }
    }
    sort(ans.begin(), ans.end());
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& s, const string& ans) {
  TEST_SMP1(Solution, originalDigits, ans, s);
}

int main() {
  Test("owoztneoer", "012");
  Test("fviefuro", "45");
  return 0;
}

#endif