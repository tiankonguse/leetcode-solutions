/*
ID: tiankonguse
TASK: detect
LANG: C++
CONTEST: CSP-S 2024
OJ: https://www.luogu.com.cn/problem/P11232?contestId=209925
*/
#define TASK "detect"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

ll t;
ll n, m, L, V;
vector<pair<ll, ll>> nums0;
vector<pair<ll, ll>> nums1;
vector<ll> caremas;
void Solver() {  //
  scanf("%lld", &t);
  while (t--) {
    nums0.clear();
    nums1.clear();
    caremas.clear();

    scanf("%lld%lld%lld%lld", &n, &m, &L, &V);
    nums0.reserve(n);
    for (ll i = 0; i < n; i++) {
      ll d, v, a;
      scanf("%lld%lld%lld", &d, &v, &a);
      if (a > 0) {
        if (v > V) {
          nums0.push_back({d, L});
        } else {
          ll S = (V + v) * (V - v) / (2 * a) + 1;
          if (d + S > L) {
            continue;
          }
          const ll r = d + S;
          const ll l = L;
          nums0.push_back({r, l});
        }
      } else if (a < 0) {  // 减速
        if (v <= V) {
          continue;
        }
        a = -a;
        ll S = (V + v) * (v - V) / (2 * a);
        if (S * 2 * a == (V + v) * (v - V)) {
          S--;
        }

        const ll r = d;
        const ll l = min(L, d + S);
        nums0.push_back({r, l});
      } else {  // 匀速
        if (v <= V) {
          continue;
        }
        nums0.push_back({d, L});
      }
    }

    caremas.resize(m);
    for (int i = 0; i < m; i++) {
      scanf("%lld", &caremas[i]);
    }

    nums1.reserve(n);  // 被拍到的车辆
    for (auto [l, r] : nums0) {
      //   printf("car [%lld,%lld]\n", l, r);
      auto it = lower_bound(caremas.begin(), caremas.end(), l);
      if (it == caremas.end()) {
        continue;
      }
      if (*it > r) {
        continue;
      }
      //   printf("find car [%lld,%lld]\n", l, r);
      nums1.push_back({l, r});
    }
    sort(nums1.begin(), nums1.end(), [](auto& a, auto& b) {
      if (a.second == b.second) {
        return a.first > b.first;
      } else {
        return a.second < b.second;
      }
    });
    // for (auto [l, r] : nums1) {
    //   printf("sort: [%lld,%lld]\n", l, r);
    // }

    ll ans = caremas.size();
    ll ni = 0;
    ll ci = 0;
    while (ci < caremas.size() && ni < nums1.size()) {
      while (ci + 1 < caremas.size() && caremas[ci + 1] <= nums1[ni].second) {
        ci++;  // 选择区间内的最后一个摄像头
      }
      //   printf("use ci=%lld\n", caremas[ci]);
      ans--;
      while (ni < nums1.size() && caremas[ci] >= nums1[ni].first) {
        // printf("ci cover[%lld,%lld]\n", nums1[ni].first, nums1[ni].second);
        ni++;  // ci 摄像头可以拍到的所有车辆
      }
      ci++;
    }
    printf("%lld %lld\n", ll(nums1.size()), ans);
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*


*/