
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
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  int minSwaps(vector<int>& A, vector<int>& B) {
    int ans = 0;
    int n = A.size();
    unordered_map<int, int> H1;
    for (int i = 0; i < n; i++) {
      int a = A[i], b = B[i];
      if (a == b) {
        H1[a]++;
      }
    }
    if (H1.empty()) return 0;

    int sameSum = 0;
    int maxVal = 0;
    int maxCnt = 0;
    for (auto [val, cnt] : H1) {
      sameSum += cnt;
      if (cnt > maxCnt) {
        maxCnt = cnt;
        maxVal = val;
      }
    }
    if (maxCnt <= sameSum - maxCnt) {  // 可以两两消除
      return (sameSum + 1) / 2;
    }
    ans += (sameSum - maxCnt);
    maxCnt -= (sameSum - maxCnt);

    for (int i = 0; i < n; i++) {
      int a = A[i], b = B[i];
      if (a == b || a == maxVal || b == maxVal) continue;
      maxCnt--;
      ans++;
      if (maxCnt == 0) return ans;
    }

    return -1;
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