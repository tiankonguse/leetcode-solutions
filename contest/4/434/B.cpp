
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
  vector<int> countMentions(int n, vector<vector<string>>& events_) {
    vector<int> users(n, 0);
    vector<int> ans(n, 0);

    vector<tuple<int, int, string>> events;
    events.reserve(events_.size() * 2);
    for (auto& e : events_) {
      const string& eventType = e[0];
      const string& eventTime = e[1];
      const string& ids = e[2];
    }
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