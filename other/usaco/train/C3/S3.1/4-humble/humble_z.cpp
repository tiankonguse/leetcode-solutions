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

int Solver(const int K) {
  unordered_set<int> H;
  min_queue<pair<ll, int>> que;
  que.push({1, 0});
  int count = 0;
  ll maxVal = 1;

  auto Add = [&H, &que, &count, &maxVal, &K](const ll v, const int index) {
    if (v > INF32) return false;
    if (H.count(v)) return true;
    if (count > K && v > maxVal) return false;

    count++;
    maxVal = max(maxVal, v);

    H.insert(v);
    que.push({v, index});
    return false;
  };

  for (int k = 1; k <= K; k++) {
    const auto [v, index] = que.top();
    que.pop();

    for (int i = 1; i <= n; i++) {
      if (!Add(v * nums[i], i)) break;
    }
    for (int i = index; i < n; i++) {
      if (!Add(v / nums[index] * nums[i + 1], i + 1)) break;
    }
  }
  printf("count=%d\n", count);
  return que.top().first;
}

void Solver() {  //
  scanf("%d%d", &n, &k);
  nums.resize(n + 1);
  nums[0] = 1;
  for (int i = 1; i <= n; i++) {
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