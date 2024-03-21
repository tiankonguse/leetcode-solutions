// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
class Solution {
 public:
  string minimizeStringValue(string s) {
    vector<int> nums(26, 0);
    vector<int> pos;
    pos.reserve(s.size());
    for (int i = 0; i < s.size(); i++) {
      char c = s[i];
      if (c == '?') {
        pos.push_back(i);
      } else {
        nums[c - 'a']++;
      }
    }
    min_queue<pair<int, int>> que;
    for (int i = 0; i < nums.size(); i++) {
      int v = nums[i];
      que.push({v, i});
    }

    vector<char> vals;
    vals.reserve(pos.size());
    for (int i = 0; i < pos.size(); i++) {
      auto [num, c] = que.top();
      que.pop();
      vals.push_back('a' + c);
      que.push({num + 1, c});
    }

    sort(vals.begin(), vals.end());
    for (int i = 0; i < pos.size(); i++) {
      s[pos[i]] = vals[i];
    }

    return s;
  }
};