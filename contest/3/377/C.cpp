// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;

void floyd(vector<vector<ll>>& mp) {  // mp[][] = inf; mp[i][i] = 0;
  int n = mp.size();
  for (int i = 0; i < n; i++) {
    mp[i][i] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (i == k) continue;
      for (int j = 0; j < n; j++) {
        if (mp[i][k] + mp[k][j] < mp[i][j]) {
          mp[i][j] = mp[i][k] + mp[k][j];
        }
      }
    }
  }
}

class Solution {
 public:
  long long minimumCost(const string& source, const string& target,
                        vector<char>& original, vector<char>& changed,
                        vector<int>& cost) {
    const int maxChar = 26;
    vector<vector<ll>> mp(26, vector<ll>(26, ninf));
    for (int i = 0; i < cost.size(); i++) {
      int u = original[i] - 'a';
      int v = changed[i] - 'a';
      ll c = cost[i];
      mp[u][v] = min(mp[u][v], c);
    }
    floyd(mp);

    ll ans = 0;
    for (int i = 0; i < source.size(); i++) {
      int u = source[i] - 'a';
      int v = target[i] - 'a';
      if (mp[u][v] == ninf) {
        return -1;
      }
      ans += mp[u][v];
    }
    return ans;
  }
};