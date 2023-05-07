// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

int dp[110][110][110];

struct node {
  int x, y, z;
} q[1000010];

class Solution {
 public:
  const int INF = 0x7f7f7f7f;

  int fx[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  int n, m;

  int hd, tl;

  void insert(int x, int y, int z, int d) {
    if (dp[x][y][z] == INF) dp[x][y][z] = d, q[++tl] = (node){x, y, z};
  }

  int extractMantra(vector<string> &s, string t) {
    n = (int)s.size();

    m = (int)s[0].size();

    for (int i = 0; i <= (int)t.size(); i++)
      for (int j = 0; j < n; j++)
        for (int k = 0; k < m; k++) dp[j][k][i] = INF;

    //	printf("%d %d %d\n",n,m,(int)t.size());

    hd = 1, tl = 0;

    insert(0, 0, 0, 0);

    if (t[0] == s[0][0]) insert(0, 0, 1, 1);

    int ans = INF;

    while (hd <= tl) {
      node A = q[hd];
      hd++;

      int x = A.x, y = A.y, z = A.z;

      if (z < (int)t.size() && t[z] == s[x][y])
        insert(x, y, z + 1, dp[x][y][z] + 1);

      //	printf("%d %d %d %d\n",x,y,z,dp[x][y][z]);

      if (z == (int)t.size()) ans = min(ans, dp[x][y][z]);

      for (int i = 0; i < 4; i++) {
        int a = x + fx[i][0], b = y + fx[i][1];

        if (0 <= a && a < n && 0 <= b && b < m) {
          insert(a, b, z, dp[x][y][z] + 1);

          // if (z<(int)t.size()&&t[z]==s[a][b]) insert(a,b,z+1,dp[x][y][z]+2);
        }
      }
    }

    if (ans == INF) ans = -1;

    return ans;
  }
};
