// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  class Help {
    int num = 0;
    unordered_map<int, int> vc;       // val -> count
    map<int, unordered_set<int>> cv;  // count -> val
   public:
    void Add(int v) {
      num++;

      int c = vc[v];
      if (c > 0) {
        cv[c].erase(v);
        if (cv[c].size() == 0) {
          cv.erase(c);
        }
      }

      vc[v] = c + 1;
      cv[c + 1].insert(v);
    }
    void Del(int v) {
      num--;

      int c = vc[v];
      cv[c].erase(v);
      if (cv[c].size() == 0) {
        cv.erase(c);
      }

      if (c - 1 > 0) {
        vc[v] = c - 1;
        cv[c - 1].insert(v);
      }
    }
    bool HasAns() {
      if (cv.size() == 0) return false;
      if (cv.rbegin()->second.size() > 1) return false;
      int c = cv.rbegin()->first;
      if (c * 2 <= num) return false;
      return true;
    }
    int Ans() {  //
      return *cv.rbegin()->second.begin();
    }
  };

 public:
  int minimumIndex(vector<int>& nums) {
    int n = nums.size();
    Help right;
    for (auto v : nums) {
      right.Add(v);
    }

    Help left;
    for (int i = 0; i + 1 < n; i++) {
      left.Add(nums[i]);
      right.Del(nums[i]);
      if (left.HasAns() && right.HasAns() && left.Ans() == right.Ans()) {
        return i;
      }
    }
    return -1;
  }
};