// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

struct SegTree {
  vector<int> maxVal;

  void Init(int n) {
    n++;
    maxNM = n;
    maxVal.resize(maxNM << 2);
  }

  void PushUp(int rt) {
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
  void Build(vector<int> score, int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      int V = 0;
      if (l < score.size()) {
        V = score[l];
      }
      maxVal[rt] = V;
      return;
    }
    int m = (l + r) >> 1;
    Build(score, lson);
    Build(score, rson);
    PushUp(rt);
  }
  int QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    int m = (l + r) >> 1;
    int ret = -1;
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;

const int N = 100100;
const int M = 10000;
int prm[M];
int K = 0;
int Getprm() {
  if (K != 0) return K;
  vector<int> is(N, 1);
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  is.clear();
  return K = k;
}

ll CalScore(ll v) {
  ll ans = 0;
  for (int i = 0; i < K && v > 1; i++) {
    if (v % prm[i] == 0) {
      ans++;
      while (v % prm[i] == 0) {
        v /= prm[i];
      }
    }
  }
  return ans;
}

// 乘法取模
ll MulMod(ll a, ll b, ll c) {
  ll res = 0LL;
  for (; b; b >>= 1, a = (a << 1) % c) {
    if (b & 1) res = (res + a) % c;
  }
  return res;
}
// 快速幂
ll PowMod(ll a, ll b, ll c) {
  ll res = 1LL;
  for (; b; b >>= 1, a = MulMod(a, a, c)) {
    if (b & 1) res = MulMod(res, a, c);
  }
  return res;
}

class Solution {
 public:
  int maximumScore(vector<int>& nums, int k) {
    Getprm();
    // printf("K=%d\n", K);

    int n = nums.size();

    segTree.Init(n);

    vector<int> score(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      score[i] = CalScore(nums[i - 1]);
    }
    segTree.Build(score);
    // for (int i = 1; i <= n; i++) {
    //   printf("i=%d score=%lld que=%lld\n", i, score[i], segTree.QueryMax(i,
    //   i));
    // }

    vector<pair<int, ll>> allScores;
    allScores.reserve(n);
    for (int i = 1; i <= n; i++) {
      // left: 小于 score[i] 的最左边界
      // right: 小于等于 score[i] 的最右边界
      ll leftPos = i, rightPos = i;
      ll V = score[i];
      int X = nums[i - 1];

      int l = 1, r = i;  // [l, r)
      while (l < r) {
        int mid = (l + r) / 2;
        ll maxVal = segTree.QueryMax(mid, i - 1);
        if (maxVal < V) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      leftPos = r;

      l = i, r = n + 1;  //[l, r)
      while (l < r) {
        int mid = (l + r) / 2;
        ll maxVal = segTree.QueryMax(i, mid);
        if (maxVal < V + 1) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      rightPos = r - 1;

      // printf("i=%d V=%lld X=%lld leftPos=%lld rightPos=%lld num=%lld\n", i,
      // V,
      //        X, leftPos, rightPos, (i - leftPos + 1) * (rightPos - i + 1));
      allScores.push_back({X, (i - leftPos + 1) * (rightPos - i + 1)});
    }

    sort(allScores.begin(), allScores.end(),
         [](auto& a, auto& b) { return a.first > b.first; });

    ll ans = 1;

    for (auto [X, num] : allScores) {
      if (k <= 0) break;

      if (num > k) {
        num = k;
      }
      k -= num;

      ans = (ans * PowMod(X, num, mod)) % mod;
    }

    return ans;
  }
};
