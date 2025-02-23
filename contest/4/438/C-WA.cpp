
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

class Solution {
 public:
  bool hasSameDigits(string s) {
    vector<int> nums;
    nums.reserve(s.size());
    for (auto c : s) {
      nums.push_back(c - '0');
    }
    int n = nums.size();
    pair<int, int> A = {0, 0}, B = {1, 1};
    for (int i = 2; i < n; i++) {
      A.second++;
      B.second++;
      if (A.second == B.first) {
        A.second--;
        B.first++;
      }
      printf("i=%d [%d,%d] [%d,%d]\n", i, A.first, A.second, B.first, B.second);
    }
    int sumA = 0, sumB = 0;
    for (int i = A.first; i <= A.second; i++) {
      sumA = (sumA + nums[i]) % 10;
    }
    for (int i = B.first; i <= B.second; i++) {
      sumB = (sumB + nums[i]) % 10;
    }
    return sumA == sumB;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() { return 0; }

#endif