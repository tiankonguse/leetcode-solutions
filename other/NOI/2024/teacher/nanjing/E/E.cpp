#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll tick = 0;
ll gcd(ll a, ll b) {
  if (!a || !b) return a ? a : b;
  ll t = a % b;
  tick++;
  while (t) {
    // printf("tick=%lld t=%lld a=%lld b=%lld \n", tick, t, a, b);
    a = b;
    b = t;
    t = a % b;
  }
  return b;
}

const int N = 1e5 + 10;
ll vals[N << 2];
ll nums[N];
ll sums[N];
int n;
void PushUp(int l = 1, int r = n, int rt = 1) {
  vals[rt] = gcd(vals[rt << 1], vals[rt << 1 | 1]);
}
void Build(int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    vals[rt] = nums[l];
    return;
  }
  int mid = (l + r) / 2;
  Build(l, mid, rt << 1);
  Build(mid + 1, r, rt << 1 | 1);
  PushUp(l, r, rt);
}
ll Query(int L, int R, int l = 1, int r = n, int rt = 1) {
  if (L <= l && R >= r) {
    return vals[rt];
  }
  int mid = (l + r) / 2;  //[l,mid] (mid+1, r]
  ll ret = 0;
  if (L <= mid) {
    ret = gcd(ret, Query(L, R, l, mid, rt << 1));
  }
  if (R > mid) {
    ret = gcd(ret, Query(L, R, mid + 1, r, rt << 1 | 1));
  }
  return ret;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    nums[0] = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &nums[i]);
      sums[i] = nums[i] + sums[i - 1];
    }
    // printf("begin Build\n");
    Build(1, n, 1);  // 初始化线段树

    ll ans = 2 * nums[1];
    ll ansL = 1, ansR = 1;
    auto updateAns = [&ans, &ansL, &ansR](ll tmpAns, ll tmpL, ll tmpR) {
      if (tmpAns > ans) {
        ans = tmpAns;
        ansL = tmpL;
        ansR = tmpR;
      }
    };
    // printf("begin loop\n");
    for (ll l = 1; l <= n; l++) {
      ll r = n;
      ll preGcd = Query(l, r, 1, n, 1);
      ll tmpAns = sums[r] - sums[l - 1] + preGcd;
      updateAns(tmpAns, l, r);
    //   printf("cal l=%lld maxGcd=%lld gcd[%lld,%lld]=%lld tmpAns=%lld\n", l,
    //          nums[l], l, r, preGcd, tmpAns);

      while (preGcd < nums[l]) {
        int L = l, R = n + 1;
        while (L < R) {  // [l, R)
          int mid = (L + R) / 2;
          ll tmpGcd = Query(l, mid, 1, n, 1);
          if (tmpGcd <= preGcd) {
            R = mid;
          } else {
            L = mid + 1;
          }
        }

        r = R - 1;
        preGcd = Query(l, r);
        ll tmpAns = sums[r] - sums[l - 1] + preGcd;
        // printf("cal l=%lld maxGcd=%lld gcd[%lld,%lld]=%lld tmpAns=%lld\n", l,
        //        nums[l], l, r, preGcd, tmpAns);
        updateAns(tmpAns, l, r);
      }
    }
    printf("%lld\n", ans);
    printf("%lld %lld\n", ansL, ansR);
  }

  return 0;
}