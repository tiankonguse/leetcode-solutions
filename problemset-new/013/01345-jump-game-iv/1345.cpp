// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minJumps(vector<int>& arr) {
    unordered_map<int, vector<int>> m;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
      m[arr[i]].push_back(i);
    }

    vector<int> flag(n, -1);
    queue<int> que;
    flag[0] = 0;
    que.push(0);

    while (flag[n - 1] == -1) {
      int x = que.front();
      que.pop();
      //前
      if (x > 0 && flag[x - 1] == -1) {
        flag[x - 1] = flag[x] + 1;
        que.push(x - 1);
      }
      //后
      if (x + 1 < n && flag[x + 1] == -1) {
        flag[x + 1] = flag[x] + 1;
        que.push(x + 1);
      }
      //相同
      int v = arr[x];
      for (auto y : m[v]) {
        if (flag[y] == -1) {
          flag[y] = flag[x] + 1;
          que.push(y);
        }
      }
      m[v].clear();
    }
    return flag[n - 1];
  }
};
