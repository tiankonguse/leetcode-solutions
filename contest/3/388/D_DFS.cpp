// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 50;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
class Solution {
  vector<vector<vector<ll>>> f;
  vector<vector<vector<ll>>> F;
  vector<int> nums;
  int K;
  int N;
  ll sign[2] = {-1, 1};

  ll DFS(int i, int n, int k) {
    ll& ret = F[i][n][k];
    if (ret != -INFL) return ret;
    const ll V = nums[n] * sign[i] * k;

    if (n == N - 1 && k == 1) {  // 最后一个
      ret = V;
    } else if (n < N - 1 && k == 1) {  // 不是最后一个，但只能选择一个
      ret = max(V, V + DFS(i, n + 1, k));
    } else if (N - n == k) {  // 每个都需要选，且都选择一个
      ret = V + DFS(1 - i, n + 1, k - 1);
    } else {
      ret = max(V + dfs(1 - i, n + 1, k - 1), V + DFS(i, n + 1, k));
    }

    return ret;
  }
  ll dfs(int i, int n, int k) {
    ll& ret = f[i][n][k];
    if (ret != -INFL) return ret;

    const ll V = nums[n] * sign[i] * k;

    if (n == N - 1 && k == 1) {  // 最后一个
      ret = V;
    } else if (n < N - 1 && k == 1) {  // 不是最后一个，但只能选择一个
      ret = max(DFS(i, n, k), dfs(i, n + 1, k));
    } else if (N - n == k) {  // 每个都需要选，且都选择一个
      ret = V + dfs(1 - i, n + 1, k - 1);
    } else {
      ret = max(dfs(i, n + 1, k), DFS(i, n, k));
    }
    return ret;
  }

 public:
  ll maximumStrength(vector<int>& nums_, const int k) {
    nums_.swap(nums);
    K = k;
    N = nums.size();
    f.resize(2, vector<vector<ll>>(N + 1, vector<ll>(K + 1, -INFL)));
    F.resize(2, vector<vector<ll>>(N + 1, vector<ll>(K + 1, -INFL)));
    return dfs(1, 0, K);
  }
};