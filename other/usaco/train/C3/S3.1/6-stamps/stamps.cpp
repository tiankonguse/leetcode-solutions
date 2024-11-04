/*
ID: tiankonguse
TASK: stamps
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "stamps"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/')+1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
}

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

ll K, N;
vector<ll> nums;
const ll KN = 2e6 + 10;
vector<int> bits;

void Solver() {  //
  scanf("%lld%lld", &K, &N);
  nums.resize(N);
  for (ll i = 0; i < N; i++) {
    scanf("%lld", &nums[i]);
  }
  sort(nums.begin(), nums.end());
  ll KN = K * nums.back();
  bits.resize(KN + 2, inf);
  for (auto v : nums) {
    bits[v] = 1;
  }

  for (ll i = 1;; i++) {
    if (bits[i] == inf) {
      printf("%lld\n", i - 1);
      break;
    }
    if (bits[i] < K) {
      for (auto v : nums) {
        ll iv = i + v;
        bits[iv] = min(bits[iv], bits[i] + 1);
      }
    }
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/