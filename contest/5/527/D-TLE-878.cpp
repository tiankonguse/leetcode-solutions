
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 超出时间限制 881 / 884 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
  unordered_map<int, int> mp;
  void Add(int v) {  //
    mp[v]++;
    if (mp[v] == 0) {
      mp.erase(v);
    }
  }
  void Remove(int v) {
    mp[v]--;
    if (mp[v] == 0) {
      mp.erase(v);
    }
  }

 public:
  vector<int> countSuffix(vector<int>& nums, vector<int>& target) {
    int n = nums.size();
    int m = target.size();
    for (auto v : nums) {
      Remove(v);
    }
    vector<int> ans;
    ans.reserve(m - n + 1);
    if (n == 1) {
      for (auto v : target) {
        if (v == nums[0]) {
          ans.push_back(1);
        } else {
          ans.push_back(0);
        }
      }
      return ans;
    }

    int orderLeft = 0, orderRight = 0;  // [orderLeft, orderRight]
    int equalPos = 0;                   // [l, equalPos)
    int equalFirst = 0;                 // [l, equalFirst)
    if (target[0] == nums[0]) {
      equalFirst = equalPos = 1;
    }
    Add(target[0]);
    int l = 0;
    for (int r = 1; r < m; r++) {  // [l, r]
      Add(target[r]);
      if (target[r - 1] >= target[r]) {
        orderRight++;
      } else {
        orderLeft = orderRight = r;
      }
      while (equalFirst < equalPos && target[equalFirst] == target[l]) {
        equalFirst++;  // 与第一个值相等的最大长度
      }
      if (r < n - 1) continue;

      MyPrintf("order: [%d,%d], equalPos: [%d,%d), equalFirst: [%d,%d)\n", orderLeft, orderRight, l, equalPos, l,
               equalFirst);
      int tmpAns = 0;
      if (mp.size() == 0) {
        while (equalPos <= r && target[equalPos] == nums[equalPos - l]) {
          equalPos++;  // 两个数字相等前缀的最大长度
        }

        int realequalPos = equalPos - 1;
        int maxAnsPos = min(realequalPos + 1, r);
        if (orderLeft <= maxAnsPos) {
          // [orderLeft, maxAnsPos]
          tmpAns = maxAnsPos - orderLeft + 1;
        }
      }
      ans.push_back(tmpAns);

      // 删除最左边的元素

      l++;
      Remove(target[l - 1]);
      // 整个区间都是有序的，所以 orderLeft 需要左移
      if (orderLeft == l - 1) {
        orderLeft++;
      }
      // 与第一个元素相等的区间 [l, equalFirst)
      if (equalFirst == l - 1) {
        // 之前没有相等的, 需要重新判断
        equalPos = equalFirst = l;
      } else {
        // 前缀相等，错位一位后，只有与第一个相等的前缀才会继续相等，之后的不可能相等
        // 与第一个位置相等的区间会变成 [l+1, equalFirst), 即 equalFirst 保持不变
        // equalFirst = equalFirst;
        // 由于错位，后续的都不相等，所以最长的相等区间与第一个相等的区间相同
        equalPos = equalFirst;
      }
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