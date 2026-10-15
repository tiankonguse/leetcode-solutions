
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
class BusBooking {
  int n;
  int cnt;
  int cost;
  vector<vector<int>> g;

  pair<int, int> Parse(const string& s) {
    int c = s[0] - 'A';
    int no = 0;
    for (int i = 1; i < s.size(); i++) {
      no = no * 10 + (s[i] - '0');
    }
    return {c, no - 1};
  }

 public:
  BusBooking(int n_) {  //
    n = n_;
    g.resize(n, vector<int>(4, 0));
    cnt = 0;
    cost = 0;
  }

  void toggle(const string& seat) {  //
    const auto [c, no] = Parse(seat);
    const int C = c ^ 1;  // 奇偶相邻的位置
    const bool side = (c == 0 || c == 3);
    if (g[no][c]) {
      // 后续取消预定，不影响之前相邻座位的状态
      // if (g[no][C] == 3) {
      //   g[no][C] = 1;
      //   cost -= 2;
      // }
      cost -= g[no][c];
      g[no][c] = 0;
      cnt--;
    } else {
      if (side && g[no][C]) {
        g[no][c] = 3;
      } else {
        g[no][c] += 1;
      }
      cost += g[no][c];
      cnt++;
    }
  }

  int getTotalTime() {  //
    return cost;
  }

  int getMinTime() {  //
    return cnt;       // 贪心：先分配靠窗的座位，再分配中间的座位，每个代价都是1秒
  }
};

/**
 * Your BusBooking object will be instantiated and called as such:
 * BusBooking* obj = new BusBooking(n);
 * obj->toggle(seat);
 * int param_2 = obj->getTotalTime();
 * int param_3 = obj->getMinTime();
 */

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif