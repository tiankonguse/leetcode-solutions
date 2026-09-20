
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
  struct Link {
    int left = 0, right = 0;
    int next = -1;
  } links[20];
  int linkOffset = 0;
  int Alloc() { return linkOffset++; }

  int Split(int id, int mid) {  // [left, mid) [ mid, right)
    int newId = Alloc();
    links[newId] = links[id];
    links[id].right = mid;
    links[id].next = newId;
    links[newId].left = mid;
    return newId;
  }
  bool HasBit(int v, int b) { return (v & (1 << b)) != 0; }
  int Count(int root, const int b, vector<int>& nums) {  //
    int cnt = 0;
    while (root != -1) {
      int left = links[root].left;
      int right = links[root].right;

      // 属于一个 block，高位全部相同
      sort(nums.begin() + left, nums.begin() + right, [&b](int A, int B) {  //
        A = A & (1 << b);
        B = B & (1 << b);
        return A > B;
      });
      if (!HasBit(nums[left], b)) {
        // 第一个就不是 1，不需要拆分
        break;
      }
      if (!HasBit(nums[right - 1], b)) {
        // 最后一个不是 1，需要拆分
        for (int i = left; i < right; i++) {
          int v = nums[i] & (1 << b);
          if (v == 0) {
            Split(root, i);
            return cnt;
          }
          cnt++;
        }
      } else {
        cnt += right - left;
        root = links[root].next;
      }
    }
    return cnt;
  }

 public:
  vector<int> largestPower(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(15);
    int root = Alloc();
    links[root].left = 0;
    links[root].right = n;
    for (int i = 0; i < 15; i++) {
      const int b = 14 - i;
      ans[i] = Count(root, b, nums);
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