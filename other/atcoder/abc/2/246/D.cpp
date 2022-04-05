#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t int128;

#define rep(i, n) for (ll i = 0; i < (n); i++)

int128 H(int128 a, int128 b) {  //
  return a * a * a + a * a * b + a * b * b + b * b * b;
}

int128 Search(int128 n, int128 b) {
  int128 l = 0, r = pow(ll(n), 1.0 / 3) + 1;
  while (l < r) {
    int128 mid = (l + r) / 2;
    if (H(mid, b) >= n) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

int128 Cal(int128 n, ll a) {
  ll b = Search(n, a);
  return H(a, b);
}

int128 Solver2(int128 n) {
  int128 l = 0, r = Search(n, 0);

  while (l + 100 < r) {
    int128 one = (r - l + 1) / 3;
    int128 mid1 = l + one, mid2 = l + one * 2;

    int128 ans1 = Cal(n, mid1);
    int128 ans2 = Cal(n, mid2);

    if (ans1 > ans2) {
      l = mid2;
    } else {
      r = mid1;
    }
  }

  int128 ans = Cal(n, l);
  while (l <= r) {
    int128 tmp = Cal(n, l);
    if (tmp < ans) {
      ans = tmp;
    }
    l++;
  }

  return ans;
}

int128 Solver1(int128 n) {
  int128 a = Search(n, 0), b = 0;
  int128 ans = H(a, b);

  bool flag = true;
  while (flag) {
    flag = false;
    if (a < b) swap(a, b);

    rep(i, 10) {
      if (i > a) break;
      int128 aa = a - i;
      int128 bb = Search(n, aa);
      int128 tmp = H(aa, bb);
      if (tmp < ans) {
        ans = tmp;
        flag = true;
      }
    }
    rep(i, 10) {
      int128 aa = a + i;
      int128 bb = Search(n, aa);
      int128 tmp = H(aa, bb);
      if (tmp < ans) {
        ans = tmp;
        flag = true;
      }
    }

    rep(i, 10) {
      if (i > b) break;
      int128 bb = b - i;
      int128 aa = Search(n, bb);

      int128 tmp = H(aa, bb);
      if (tmp < ans) {
        ans = tmp;
      }
    }
    rep(i, 10) {
      int128 bb = b - 1;
      int128 aa = Search(n, bb);

      int128 tmp = H(aa, bb);
      if (tmp < ans) {
        ans = tmp;
      }
    }
  }
  return ans;
}

int main() {
  ll n;
  scanf("%lld", &n);
  printf("%lld\n", min(ll(Solver1(n)), ll(Solver2(n))));
  return 0;
}
