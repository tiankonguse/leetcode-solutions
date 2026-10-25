
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
typedef long long ll;

/*
第三题与第四题完全一样，至少数据范围的不同，所以可以考虑直接写出一个最优解，依次过两道题。  

题目要求，对于一个子数组，需要满足恰好第k个出现的不同数字的频次是 K。  

先看满足这样的子数组上限是多少个。  
枚举每个起始位置 i，然后枚举k的个数，则 k 最多不超过 `sqrt(n-i)`
故，满足这样的子数组上限是 `n * sqrt(n)` 个。

显然，这道题的解法是 O(n * sqrt(n)) 的复杂度。

我们只需要枚举每个起始位置，以及每个 k，判断是否满足条件即可。


对于一个起始位置 i，第一个不同值就是位置 i，一定满足要求。  
如何找到下一个不同值呢？  

针对第一个不同值问题，普遍的解题思路是预处理，将第一次出现该值的位置标记为1，之后出现的位置标记为0。  

如果使用线段树，就可以二分找到下个值为 1 的位置了。  
复杂度比较高，为 `log(n) * log(n)`。  


另一个思路是使用最小堆，把标记为 1 的位置让到堆里面。  
堆顶默认是起始位置，弹出起始位置，下一个堆顶就是下一个不同值的位置。
复杂度就只有 `O(log(n))`了。  


找到下个不同值的位置了，如何判断是否满足有 k 个呢？  
这就需要预处理每个不同值的位置列表。  


比如存了每个不同值的所有位置升序列表。  
可以二分找到当前位置在列表中的位置，然后判断加 K 是否超过列表的长度。
超过了，则不够 k 个，当前起始位置的后续 K 也都不满足要求，结束当前起始位置的枚举。  
够 K 个了，找到第 K 个的位置，枚举子数组的右边界需要至少覆盖第 K 个位置。


这里升序存储需要使用二分查找。  
改成逆序存储，及时清理小于起始位置的数据，则列表中最后一个位置就是要找的下一个不同值的位置。
这样复杂度可以降低到 `O(1)`  


第 K 个不同值的 K 个位置全部找到了，就可以判断当前子数组是否是答案了。  
可以证明，只要满足 `(1+k)*k/2 == R-L+1`，当前子数组就一定是答案。


证明需要使用归纳法。  
第 1 个不同值只有 1 个，显然成立。  
第 2 个不同值预期是 2个，等式成立后，与第一个不同值相比，也恰好多了 2 个值，所以也成立。  
同理，第 k 个不同值预期是 k 个，等式成立后，与第 k-1 个不同值相比，也恰好多了 k 个值，所以也成立。  


由此，边可以枚举每个起始位置，以及每个 k，判断是否满足条件即可。  
总复杂度：`O(n * sqrt(n) * log(n))`


*/

class Solution {
 public:
  int countStaircase(vector<int>& nums) {
    const int n = nums.size();
    unordered_map<ll, vector<ll>> valPos;
    min_queue<pair<ll, ll>> minHeap;
    for (int i = 0; i < n; i++) {
      valPos[nums[i]].push_back(i);
    }
    for (auto& [val, ps] : valPos) {
      std::reverse(ps.begin(), ps.end());
      minHeap.push({ps.back(), val});
      MyPrintf("val=%lld, pos: ", val);
      for (int i = 0; i < ps.size(); i++) {
        MyPrintf("%lld ", ps[i]);
      }
      MyPrintf("\n");
    }
    ll ans = 0;
    vector<pair<ll, ll>> sta;
    sta.reserve(n);
    for (int i = 0; i < n; i++) {
      const ll v = nums[i];
      MyPrintf("begin i=%d, v=%lld\n", i, v);
      ll L = i, R = i;
      for (ll k = 1;; k++) {
        const ll expLen = (1 + k) * k / 2;
        if (i + expLen > n) {
          MyPrintf("i + expLen=%lld, n=%d, i + expLen > n, break\n", i + expLen, n);
          break;
        }
        if (minHeap.empty()) {
          MyPrintf("minHeap.empty(), break\n");
          break;
        }
        sta.push_back(minHeap.top());
        auto [pos, val] = minHeap.top();
        minHeap.pop();
        ll valCnt = valPos[val].size();
        MyPrintf("next pos=%lld, val=%lld valCnt=%lld\n", pos, val, valCnt);
        if (valCnt < k) {
          MyPrintf("valCnt=%lld < k=%lld, break\n", valCnt, k);
          break;
        }
        ll valLastPos = valPos[val][valCnt - k];
        R = max(R, valLastPos);
        MyPrintf("valLastPos=%lld, R=%lld\n", valLastPos, R);
        MyPrintf("k=%lld expLen=%lld, R-L+1=%lld\n", k, expLen, R - L + 1);
        if (expLen == (R - L + 1)) {
          MyPrintf("ans++\n");
          ans++;
        }
      }
      while (!sta.empty()) {
        minHeap.push(sta.back());
        sta.pop_back();
      }
      MyPrintf("minHeap.pop(), val=%lld pos=%lld\n", minHeap.top().second, minHeap.top().first);
      minHeap.pop();
      valPos[v].pop_back();
      if (!valPos[v].empty()) {
        MyPrintf("minHeap.push(), val=%lld, pos=%lld\n", v, valPos[v].back());
        minHeap.push({valPos[v].back(), v});
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