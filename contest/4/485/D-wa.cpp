
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
  string lexSmallestAfterDeletion(string s) {
    vector<vector<int>> links(26);
    for (int i = 0; i < s.size(); i++) {
      links[s[i] - 'a'].push_back(i);
    }

    set<int> prePos;
    for (int i = 0; i < 26; i++) {
      if (links[i].empty()) continue;
      const char c = 'a' + i;
      // 判断 c 是否可以作为 ans 下一个字符
      if (prePos.empty()) {
        prePos.insert(links[i][0]);  // 作为最小值，越往前越好
      } else {
        const int preMaxPos = *prePos.rbegin();
        int nowMinPos = links[i].back();
        links[i].pop_back();
        // 找到最小的且大于 preMaxPos 的位置
        while (links[i].size() > 0 && links[i].back() > preMaxPos) {
          nowMinPos = links[i].back();
          links[i].pop_back();
        }
        prePos.insert(nowMinPos);
      }
    }
    string ans;
    ans.reserve(s.size());
    for (auto pos : prePos) {
      ans.push_back(s[pos]);
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