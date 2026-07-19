
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
 public:
  int minRotation(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    string ss = s + s;

    int i = 0, j = 1;
    while (i < n && j < n) {
      int k = 0;
      while (k < n && ss[i + k] == ss[j + k]) ++k;
      if (k == n) break;

      if (ss[i + k] > ss[j + k]) {
        i += k + 1;
        if (i == j) ++i;
      } else {
        j += k + 1;
        if (i == j) ++j;
      }
    }
    return min(i, j);
  }

  string canonical(string s) {
    if (s.empty()) return "";

    int pos = minRotation(s);

    return s.substr(pos) + s.substr(0, pos);
  }

  int minimumGroups(vector<string>& words) {
    unordered_set<string> st;

    for (auto& w : words) {
      string even, odd;

      for (int i = 0; i < (int)w.size(); i++) {
        if (i & 1)
          odd += w[i];
        else
          even += w[i];
      }

      string key = canonical(even);
      key.push_back('#');
      key += canonical(odd);

      st.insert(key);
    }

    return st.size();
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