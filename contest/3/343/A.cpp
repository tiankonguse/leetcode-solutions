// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Cal(vector<int>& player) {
    int ans = 0;
    int p = -10;
    for (int i = 0; i < player.size(); i++) {
      int v = player[i];
      ans += v;
      if (p + 2 >= i) {
        ans += v;
      }
      if (v == 10) {
        p = i;
      }
    }

    return ans;
  }

 public:
  int isWinner(vector<int>& player1, vector<int>& player2) {
    int a = Cal(player1);
    int b = Cal(player2);
    if (a > b) {
      return 1;
    } else if (a < b) {
      return 2;
    } else {
      return 0;
    }
  }
};
