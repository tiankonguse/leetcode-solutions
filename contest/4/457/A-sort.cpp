
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
  bool IsValidateCode(const string& code) {
    if (code.empty()) return false;
    for (auto c : code) {
      if ('0' <= c && c <= '9') continue;
      if ('a' <= c && c <= 'z') continue;
      if ('A' <= c && c <= 'Z') continue;
      if (c == '_') continue;
      return false;
    }
    return true;
  }

 public:
  vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
    int n = code.size();
    set<string> s = {"electronics", "grocery", "pharmacy", "restaurant"};
    vector<int> ansIndex;
    for (int i = 0; i < n; i++) {
      if (!isActive[i]) {
        continue;
      }
      if (!IsValidateCode(code[i])) {
        continue;
      }
      if (!s.count(businessLine[i])) {
        continue;
      }
      ansIndex.push_back(i);
    }
    sort(ansIndex.begin(), ansIndex.end(), [&](int a, int b) {
      if (businessLine[a] == businessLine[b]) {
        return code[a] < code[b];
      }
      return businessLine[a] < businessLine[b];
    });
    vector<string> ans;
    for (int i = 0; i < ansIndex.size(); i++) {
      ans.push_back(code[ansIndex[i]]);
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