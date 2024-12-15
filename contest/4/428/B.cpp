
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
  double maxAmount(string s, vector<vector<string>>& pairs1,
                   vector<double>& rates1, vector<vector<string>>& pairs2,
                   vector<double>& rates2) {
    unordered_map<string, double> H[2];
    unordered_map<string, vector<pair<string, double>>> h[2];
    int n1 = pairs1.size();
    int n2 = pairs2.size();

    // string& s = pairs1[i][0];
    // string& t = pairs1[i][1];
    // double r = rates1[i];
    for (int i = 0; i < n1; i++) {
      h[0][pairs1[i][0]].push_back({pairs1[i][1], rates1[i]});
      h[0][pairs1[i][1]].push_back({pairs1[i][0], 1 / rates1[i]});
    }
    for (int i = 0; i < n2; i++) {
      h[1][pairs2[i][0]].push_back({pairs2[i][1], rates2[i]});
      h[1][pairs2[i][1]].push_back({pairs2[i][0], 1 / rates2[i]});
    }

    auto bfs = [&h, &H](const string& s, double d, int index) {
      auto& H1 = H[index];
      auto& h1 = h[index];
      queue<string> que;

      auto Add = [&H1, &que](const string& t, double D) {
        if (H1.count(t) == 0) {
          H1[t] = D;
          que.push(t);
        } else if (H1[t] < D) {
          H1[t] = D;
          que.push(t);
        }
      };

      Add(s, d);

      while (!que.empty()) {
        auto s = que.front();
        que.pop();
        double d = H1[s];
        if (!h1.count(s)) continue;
        for (auto& [t, r] : h1[s]) {  //
          Add(t, d * r);
        }
      }
    };

    bfs(s, 1.0, 0);

    for (auto& [s, d] : H[0]) {
      bfs(s, d, 1);
    }
    return H[1][s];
  };
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