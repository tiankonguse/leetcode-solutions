
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
  int ToSecond(const string& time) {
    int hour = 0, minute = 0, second = 0;
    sscanf(time.c_str(), "%d:%d:%d", &hour, &minute, &second);
    return hour * 3600 + minute * 60 + second;
  }

 public:
  int secondsBetweenTimes(string startTime, string endTime) {
    int startSecond = ToSecond(startTime);
    int endSecond = ToSecond(endTime);
    return endSecond - startSecond;
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