
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 超出时间限制 996 / 999 个通过的测试用例

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

  /*
  
  
第三题与第四题完全一样，至少数据范围的不同，所以可以考虑直接写出一个最优解，依次过两道题。  


第三题的代码在第四题上提交后，在 第 996 / 999 个测试用例上超时了。  


分析代码，可以发现还有一个情况我们没有使用。  
当枚举到第 k 个不同值时，如果前面的不同值个数超过自身时，后续也是都没有答案的。  


正常情况，枚举第 K 个再去判断前面 K 个值，复杂度就会退化为 `n * sqrt(n) * sqrt(n)`，即 `O(n^2)` 的复杂度。  


观察反例，某个不同值不满足 第 k 个不同值等于自身的频次时，代表频次为 `k+1` 的位置也被子数组覆盖了。  
也就是说，对于第 k 个不同值，所有子数组的右边界都不能覆盖第 `k+1`个频次的位置。  
所以，可以维护这样一个右边界的上限，枚举每个不同值后，更新这个上限，然后判断是否满足条件。  


总复杂度不变还是：`O(n * sqrt(n) * log(n))`
不过增加了一个剪枝，就可以通过这道题了。  





  */
  
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
typedef long long ll;
min_queue<pair<ll, ll>> minHeap;
vector<pair<ll, ll>> sta;
class Solution {
 public:
  int countStaircase(vector<int>& nums) {
    const int n = nums.size();
    unordered_map<ll, vector<ll>> valPos;
    while (!minHeap.empty()) {
      minHeap.pop();
    }
    for (int i = 0; i < n; i++) {
      valPos[nums[i]].push_back(i);
    }
    for (auto& [val, ps] : valPos) {
      std::reverse(ps.begin(), ps.end());
      minHeap.push({ps.back(), val});
      MyPrintf("val=%lld, pos: ", val);
      // for (int i = 0; i < ps.size(); i++) {
      //   MyPrintf("%lld ", ps[i]);
      // }
      MyPrintf("\n");
    }
    ll ans = 0;
    sta.reserve(n);
    sta.clear();
    for (int i = 0; i < n; i++) {
      const ll v = nums[i];
      MyPrintf("begin i=%d, v=%lld\n", i, v);
      ll L = i, R = i;
      ll limitPos = n;
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
        if (k < valCnt) {
          limitPos = min(limitPos, valPos[val][valCnt - k - 1]);
        }
        MyPrintf("valLastPos=%lld, R=%lld\n", valLastPos, R);
        MyPrintf("k=%lld expLen=%lld, R-L+1=%lld\n", k, expLen, R - L + 1);
        if (expLen == (R - L + 1)) {
          MyPrintf("ans++\n");
          ans++;
        }
        if (R >= limitPos) {
          break;
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