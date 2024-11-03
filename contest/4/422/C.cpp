
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

typedef long long ll;
int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

const int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
const int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                        {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
typedef long long ll;
class Solution {
 public:
  int minTimeToReach(vector<vector<int>>& moveTime) {
    int n = moveTime.size();
    int m = moveTime[0].size();
    vector<vector<ll>> flag(n, vector<ll>(m, inf));
    min_queue<tuple<ll, ll, ll>> que;
    que.push({0, 0, 0});
    flag[0][0] = 0;
    while (!que.empty()) {
      const auto [d, x, y] = que.top();
      que.pop();
      for (int i = 0; i < 4; i++) {
        const ll X = x + dir4[i][0];
        const ll Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
        const ll D = max(d, ll(moveTime[X][Y])) + (2 - ((X + Y) % 2));
        if (D < flag[X][Y]) {
          flag[X][Y] = D;
          que.push({D, X, Y});
        }
      }
    }
    return flag[n - 1][m - 1];
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<vector<int>>& moveTime, const int& ans) {
  TEST_SMP1(Solution, minTimeToReach, ans, moveTime);
}

int main() {
  Test(vector<vector<int>>({{0, 4}, {4, 4}}), 7);
  Test(vector<vector<int>>({{0, 0, 0, 0}, {0, 0, 0, 0}}), 6);
  Test(vector<vector<int>>({{0, 1}, {1, 2}}), 4);
  Test(vector<vector<int>>({{0,58}, {27,69}}), 71);

  return 0;
}

#endif