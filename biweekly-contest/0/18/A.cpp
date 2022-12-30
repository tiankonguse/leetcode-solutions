// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> arrayRankTransform(vector<int>& arr) {
    map<int, int> m;
    for (auto v : arr) {
      m[v] = 0;
    }

    int index = 1;
    for (auto& [k, v] : m) {
      v = index++;
    }
    for (auto& v : arr) {
      v = m[v];
    }
    return arr;
  }
};