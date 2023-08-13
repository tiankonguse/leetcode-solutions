// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;


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

    vector<int> score(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      score[i] = CalScore(nums[i - 1]);
    }
    vector<int> leftPos(n+1), rightPos(n+1);
    vector<int> sta;
    for(int i=1;i<=n;i++){
      while(!sta.empty() && score[sta.back()] < score[i]){
        sta.pop_back();
      }
      if(sta.empty()){
        leftPos[i] = 1;
      }else{
        leftPos[i] = sta.back() + 1;
      }
      sta.push_back(i);
    }

    sta.clear();
    for(int i=n;i>=1;i--){
      while(!sta.empty() && score[sta.back()] <= score[i]){
        sta.pop_back();
      }
      if(sta.empty()){
        rightPos[i] = n;
      }else{
        rightPos[i] = sta.back() - 1;
      }
      sta.push_back(i);
    }

    vector<pair<int, ll>> allScores;
    allScores.reserve(n);
    for (int i = 1; i <= n; i++) {
      // left: 小于 score[i] 的最左边界
      // right: 小于等于 score[i] 的最右边界
      int X = nums[i - 1];
      allScores.push_back({X, (i - leftPos[i] + 1) * (rightPos[i] - i + 1)});
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
