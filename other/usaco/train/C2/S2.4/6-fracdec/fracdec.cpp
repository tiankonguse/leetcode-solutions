/*
ID: tiankonguse
TASK: fracdec
LANG: C++
*/
#define TASK "fracdec"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n, d;
unordered_map<ll, ll> h;
void Solver() {  //
  scanf("%lld%lld", &n, &d);
  ll left = n / d;
  ll right = n % d;
  string ans = to_string(left);
  ans.push_back('.');

  int repeat = 0;
  do {
    n = right * 10;
    if (h.count(n)) {
      repeat = h[n];
      break;
    }
    left = n / d;
    right = n % d;
    ans.push_back('0' + left);
    h[n] = ans.size() - 1;
  } while (right > 0);

  if (repeat != 0) {
    ans.insert(ans.begin() + repeat, '(');
    ans.push_back(')');
  }
  int line = 0;
  for (size_t i = 0; i < ans.size(); i++) {
    printf("%c", ans[i]);
    if (i % 76 == 75) {
      line = 0;
      printf("\n");
    } else {
      line = 1;
    }
  }
  if (line == 1) {
    printf("\n");
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/