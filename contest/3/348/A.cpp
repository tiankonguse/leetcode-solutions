// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimizedStringLength(string s) {
    unordered_set<char> h;
    for (auto c : s) {
      h.insert(c);
    }
    return h.size();
  }
};