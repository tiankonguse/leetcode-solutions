
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
/*
You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.

For each index i from 0 to n - 1, perform the following:

Find all indices j where nums1[j] is less than nums1[i].
Choose at most k values of nums2[j] at these indices to maximize the total sum.
Return an array answer of size n, where answer[i] represents the result for the corresponding index i.
*/
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  vector<ll> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
    int n = nums1.size();

    vector<pair<ll, ll>> nums12;
    for (int i = 0; i < n; i++) {
      nums12.push_back({nums1[i], nums2[i]});
    }
    sort(nums12.begin(), nums12.end());

    vector<ll> preMaxK(n + 1, 0);
    min_queue<ll> que;  // 最多 K 个 nums2[j]
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      que.push(nums12[i].second);
      sum += nums12[i].second;
      if (que.size() > k) {
        sum -= que.top();
        que.pop();
      }
      preMaxK[i + 1] = sum;
    }

    vector<ll> ans(n, 0);
    for (int i = 0; i < n; i++) {
      pair<ll, ll> p = {nums1[i], -1};
      int offset = upper_bound(nums12.begin(), nums12.end(), p) - nums12.begin();
      ans[i] = preMaxK[offset];
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