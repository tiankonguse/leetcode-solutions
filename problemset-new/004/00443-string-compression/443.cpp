
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
  int ans = 0;
  vector<char> ansStr;
  void UpdateAns(char c, int n) {
    ansStr.push_back(c);
    ans++;
    if (n > 1) {
      string s = to_string(n);
      ans += s.size();
      ansStr.insert(ansStr.end(), s.begin(), s.end());
    }
  }
  int compress(vector<char>& chars) {
    char preVal = ' ';
    int preNum = 0;
    for (auto v : chars) {
      if (v == preVal) {
        preNum++;
      } else {
        if (preNum > 0) {
          UpdateAns(preVal, preNum);
        }
        preNum = 1;
        preVal = v;
      }
    }
    UpdateAns(preVal, preNum);
    chars.swap(ansStr);
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<char> chars, const int& ans) {
  TEST_SMP1(Solution, compress, ans, chars);
}

int main() {
  Test({'a', 'a', 'b', 'b', 'c', 'c', 'c'}, 6);
  Test({'a'}, 1);
  Test({'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}, 4);
  return 0;
}

#endif