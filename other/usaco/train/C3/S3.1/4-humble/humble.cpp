/*
ID: tiankonguse
TASK: humble
LANG: C++
*/
#define TASK "humble"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INF32 = 1LL << 32;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int k, n;
vector<int> nums;
unordered_set<int> H;

int Solver(const int K) {
  min_queue<int> que;
  que.push(1);
  int count = 0;
  ll maxVal = 1;

  for (int k = 1; k <= K; k++) {
    const ll v = que.top();
    que.pop();
    // printf("k=%lld v=%lld\n", k, v);

    for (ll i = 0; i < n; i++) {
      const ll V = v * nums[i];
      if (V > INF32) break;
      if (H.count(V)) continue;
      if (count > K && V > maxVal) break;

      count++;
      maxVal = max(maxVal, V);

      H.insert(V);
      que.push(V);
    }
  }
  printf("count=%d\n", count);
  return que.top();
}

void Solver() {  //
  scanf("%d%d", &n, &k);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  sort(nums.begin(), nums.end());

  printf("%d\n", Solver(k));
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/