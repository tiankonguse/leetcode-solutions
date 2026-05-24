
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
struct Block {
  Block() {
    cnt.clear();
    lazy = 0;
  }
  unordered_map<ll, int> cnt;
  ll lazy = 0;
};
struct SqrtBlock {
  vector<int> nums;
  vector<Block> blocks;
  int blockSize;
  int blockCnt;
  void Init(const vector<int>& nums) {
    int n = nums.size();
    this->nums = nums;
    blockSize = max(1, (int)sqrt(n));
    blockCnt = (n + blockSize - 1) / blockSize;
    blocks.clear();
    blocks.resize(blockCnt);
    for (int i = 0; i < n; i++) {
      int b = i / blockSize;
      blocks[b].cnt[nums[i]]++;
    }
  }
  void Update(const int l, const int r, const ll val) {
    int startBlock = l / blockSize;
    int endBlock = r / blockSize;
    if (startBlock == endBlock) {
      for (int i = l; i <= r; i++) {
        blocks[startBlock].cnt[nums[i]]--;
        nums[i] += val;
        blocks[startBlock].cnt[nums[i]]++;
      }
    } else {
      {  // 左半部
        int L = l;
        int R = (startBlock + 1) * blockSize - 1;
        for (int i = L; i <= R; i++) {
          blocks[startBlock].cnt[nums[i]]--;
          nums[i] += val;
          blocks[startBlock].cnt[nums[i]]++;
        }
      }
      {  // 中间
        for (int b = startBlock + 1; b < endBlock; b++) {
          blocks[b].lazy += val;
        }
      }
      {  // 右半部
        int L = endBlock * blockSize;
        int R = r;
        for (int i = L; i <= R; i++) {
          blocks[endBlock].cnt[nums[i]]--;
          nums[i] += val;
          blocks[endBlock].cnt[nums[i]]++;
        }
      }
    }
  }
  ll Query(const int l, const int r, const ll tot) {
    ll ret = 0;

    int startBlock = l / blockSize;
    int endBlock = r / blockSize;
    if (startBlock == endBlock) {
      for (int i = l; i <= r; i++) {
        if (nums[i] + blocks[startBlock].lazy == tot) {
          ret++;
        }
      }
    } else {
      {  // 左半部
        int L = l;
        int R = (startBlock + 1) * blockSize - 1;
        for (int i = L; i <= R; i++) {
          if (nums[i] + blocks[startBlock].lazy == tot) {
            ret++;
          }
        }
      }
      {  // 中间
        for (int b = startBlock + 1; b < endBlock; b++) {
          ll realTarget = tot - blocks[b].lazy;
          if (blocks[b].cnt.count(realTarget)) {
            ret += blocks[b].cnt[realTarget];
          }
        }
      }
      {  // 右半部
        int L = endBlock * blockSize;
        int R = r;
        for (int i = L; i <= R; i++) {
          if (nums[i] + blocks[endBlock].lazy == tot) {
            ret++;
          }
        }
      }
    }

    return ret;
  }
};

SqrtBlock sqrtBlock;
class Solution {
 public:
  vector<int> numberOfPairs(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {  //
    int m = nums1.size(), n = nums2.size();
    vector<int> ans;
    ans.reserve(queries.size());
    sqrtBlock.Init(nums2);
    for (const auto& q : queries) {
      int op = q[0];
      if (op == 1) {
        int x = q[1], y = q[2];
        ll val = q[3];
        sqrtBlock.Update(x, y, val);
      } else {
        ll tot = q[1];
        ll ret = 0;
        for (ll v : nums1) {
          ll target = tot - v;
          ret += sqrtBlock.Query(0, n - 1, target);
        }
        ans.push_back(ret);
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