
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
  vector<int> findAnagrams(const string& s, const string& p) {
    int n = s.size();
    int k = p.size();
    vector<int> ans;
    if (k > n) return ans;

    ans.reserve(n);
    unordered_map<char, int> cnt;
    for (auto c : p) {
      cnt[c]++;
    }
    for (int i = 0; i < n; i++) {
      cnt[s[i]]--;
      if (cnt[s[i]] == 0) {
        cnt.erase(s[i]);
      }

      if (i < k - 1) continue;
      if (cnt.empty()) {
        ans.push_back(i - k + 1);
      }
      cnt[s[i - k + 1]]++;
      if (cnt[s[i - k + 1]] == 0) {
        cnt.erase(s[i - k + 1]);
      }
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif