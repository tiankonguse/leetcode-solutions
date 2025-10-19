
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
  map<char, int> H;
  int n;
  string ans;
  string target;

  bool Dfs(int i) {
    if (i == n) return false;  // 说明全部相等
    const char c = target[i];
    if (H.count(c)) {
      H[c]--;
      if (H[c] == 0) H.erase(c);
      ans.push_back(c);
      if (Dfs(i + 1)) return true;
      H[c]++;
      ans.pop_back();
    }
    auto it = H.upper_bound(c);
    if (it == H.end()) return false;
    ans.push_back(it->first);
    H[it->first]--;
    if (H[it->first] == 0) H.erase(it->first);
    for (auto& p : H) {
      ans.append(string(p.second, p.first));
    }
    return true;
  }

 public:
  const string& lexGreaterPermutation(string s, string target_) {
    target.swap(target_);
    n = s.size();
    sort(s.begin(), s.end());
    std::reverse(s.begin(), s.end());
    MyPrintf("s=%s target=%s\n", s.c_str(), target.c_str());
    for (char c : s) H[c]++;
    Dfs(0);
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