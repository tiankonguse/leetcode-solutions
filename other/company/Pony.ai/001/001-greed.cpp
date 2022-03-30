// #include "base.h"

#include <bits/stdc++.h>
using namespace std;

typedef __int128_t int128;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;

typedef long double ld;
typedef vector<ld> vld;

typedef vector<bool> vb;
typedef vector<string> vs;

// const int mod = 1e9 + 7;

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define rep1(i, n) for (ll i = 1; i <= (n); i++)
#define rrep(i, n) for (ll i = (n)-1; i >= 0; i--)
#define rrep1(i, n) for (ll i = (n); i >= 1; i--)
#define all(v) (v).begin(), (v).end()

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

template <class T>
void chmin(T& a, T b) {
  a = min(a, b);
}
template <class T>
void chmax(T& a, T b) {
  a = max(a, b);
}

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

vvll m;
vvll sums;
ll r = 100;
ll d;

void Init(ll n) {
  d = 2 * r + 1;
  m.resize(d + 1, vll(d + 1, 0));
  m[r][r] = n;

  bool flag = true;
  while (flag) {
    flag = false;
    rep(i, d) {
      rep(j, d) {
        ll v = m[i][j];
        if (v < 8) continue;
        // printf("i=%lld j=%lld v=%lld\n", i, j, v);
        flag = true;
        rep(k, 8) {
          ll x = i + dir8[k][0], y = j + dir8[k][1];
          m[x][y] += v / 8;
        }
        m[i][j] %= 8;
        // printf("i=%lld j=%lld v=%lld\n", i, j, m[i][j]);
      }
    }
  }

  sums.resize(d + 1, vll(d + 1, 0));
  rep(i, d) {
    rep(j, d) {
      //   if (m[i][j] > 0) printf("i=%lld j=%lld v=%lld\n", i, j, m[i][j]);
      if (i == 0 && j == 0)
        sums[i][j] = m[i][j];
      else if (i == 0)
        sums[i][j] = m[i][j] + sums[i][j - 1];
      else if (j == 0)
        sums[i][j] = m[i][j] + sums[i - 1][j];
      else
        sums[i][j] =
            m[i][j] + sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];
    }
  }
}

ll Solver(ll x1, ll y1, ll x2, ll y2) {
  x1 += r, y1 += r, x2 += r, y2 += r;

  x1 = max(x1, 1ll);
  y1 = max(y1, 1ll);
  x2 = min(x2, d - 1);
  y2 = min(y2, d - 1);
  if (x1 > x2 || y1 > y2) {
    return 0;
  }
  return sums[x2][y2] - sums[x2][y1 - 1] - sums[x1 - 1][y2] +
         sums[x1 - 1][y1 - 1];
}

int main() {
  ll n, q;
  scanf("%lld%lld", &n, &q);
  Init(n);

  while (q--) {
    ll x1, y1, x2, y2;
    scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
    printf("%lld\n", Solver(x1, y1, x2, y2));
  }

  return 0;
}
