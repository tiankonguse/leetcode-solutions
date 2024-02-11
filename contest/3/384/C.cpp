// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxPalindromesAfterOperations(vector<string>& words) {
    map<char, int> h;
    vector<int> nums;
    nums.reserve(words.size());
    for (auto& w : words) {
      nums.push_back(w.length());
      for (auto c : w) {
        h[c]++;
      }
    }
    int one = 0, two = 0;
    for (auto [k, v] : h) {
      two += v / 2;
      one += v % 2;
    }

    int ans = 0;
    sort(nums.begin(), nums.end());
    for (auto v : nums) {
      if (v % 2 == 0) {
        if (v / 2 <= two) {
          ans++;
          two -= v / 2;
        } else {
          break;
        }
      } else {
        if (one == 0 && two > 0) {
          one += 2;
          two -= 1;
        }
        if (v / 2 <= two && one > 0) {
          ans++;
          two -= v / 2;
          one--;
        } else {
          break;
        }
      }
    }
    return ans;
  }
};
