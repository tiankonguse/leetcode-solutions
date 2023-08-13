// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool canVisitAllRooms(vector<vector<int>>& rooms) {
    stack<int> sta;
    vector<int> have(rooms.size(), 0);
    int ans = 1;
    sta.push(0);
    have[0] = 1;

    while (!sta.empty()) {
      auto pos = sta.top();
      sta.pop();

      auto& v = rooms[pos];
      for (int i = 0; i < v.size(); i++) {
        if (have[v[i]]) continue;
        ans++;
        sta.push(v[i]);
        have[v[i]] = 1;
      }
    }

    return ans == rooms.size();
  }
};  
