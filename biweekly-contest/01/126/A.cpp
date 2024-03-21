// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int sumOfEncryptedInt(vector<int>& nums) {
    int ans = 0;
    for (auto v : nums) {
      int k = 0;
      int V = 0;
      while (v) {
        V = max(V, v % 10);
        v /= 10;
        k++;
      }
      int base = 1;
      for(int i=0;i<k;i++){
        ans += base * V;
        base *= 10;
      }
    }
    return ans;
  }
};