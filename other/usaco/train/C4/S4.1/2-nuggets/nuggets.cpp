/*
ID: tiankonguse
TASK: nuggets
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "nuggets"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; (t = x % y); x = y, y = t);
  return y;
}

int n;
vector<int> nums;
vector<int> bits;
const int N = 1000;
const int N2 = N / 2;
void Solver() {  //
  scanf("%d", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  int v = nums[0];
  for (int i = 0; i < n; i++) {
    v = Gcd(v, nums[i]);
  }
  sort(nums.begin(), nums.end());
  if (v > 1 || nums[0] == 1) {
    printf("0\n");
    return;
  }
  bits.resize(N, 0);
  int ans = 1;
  int index = 0;
  int offset = 0;
  bits[0] = 1;
  int num = 0;
  while (true) {
    assert(index < N);
    if (bits[index] == 1) {
      for (auto v : nums) {
        assert(index + v < N);
        bits[index + v] = 1;
      }
      num++;
    } else {
      ans = index + offset;
      num = 0;
    }
    if (num >= nums[0]) break;

    index++;

    if (index == N2) {
      for (int i = 0, j = N2; j < N; j++, i++) {
        bits[i] = bits[j];
        bits[j] = 0;
      }
      index -= N2;
      offset += N2;
    }
  }
  printf("%d\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/