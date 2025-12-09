
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
  ll totalScore(ll hp, vector<int>& damage, vector<int>& requirement) {
    int n = damage.size();
    vector<ll> leftHp(n + 1);  // 第一关剩余的血量
    map<ll, ll> mp;
    leftHp[0] = hp;
    for (int i = 1; i <= n; i++) {
      ll d = damage[i - 1];
      ll r = requirement[i - 1];
      leftHp[i] = leftHp[i - 1] - d;
      mp[leftHp[i] - r]++;
    }
    ll ans = 0;
    ll okNum = 0;  // 当前剩余关卡得分的个数
    ll add = 0;
    for (int i = 1; i <= n; i++) {
      const ll d = damage[i - 1];
      const ll r = requirement[i - 1];
      // 第一步：计算从第 i 关开始的得分
      while (!mp.empty()) {
        auto it = mp.end();
        it--;
        if (it->first + add < 0) {
          break;
        }
        okNum += it->second;  // 大于关卡分数的个数
        mp.erase(it);
      }
      ans += okNum;
      
      // 第二步：删除第 i 关
      if (leftHp[i] - r + add >= 0) {
        okNum--;  // 这个关卡已经得分了，不在队里中
      } else {
        mp[leftHp[i] - r]--;  // 一定在队列中，减少计数，统计得分时再出队
      }

      // 第三步：延迟标记，后续的血量都上升 d
      add += d;
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