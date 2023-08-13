// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> splitIntoFibonacci(string num) {
    vector<int> ans;
    int n = num.size();
    const char* p = num.data();

    auto check = [&](ll a, ll b, int k) -> bool {
      ans.clear();
      ans.push_back(a);
      ans.push_back(b);

      if (k == n) return false;  // 只有两个

      while (k < n) {
        ll c = a + b;
        if(c > INT_MAX) return false;
        string s = to_string(c);
        if (strncmp(s.data(), p + k, s.size()) != 0) {
          return false;
        }
        ans.push_back(c);
        a = b;
        b = c;
        k += s.size();
      }

      return k == n;
    };

    string first;
    for (int i = 0; i < n; i++) {
      first.push_back(num[i]);
      if (first.size() > 1 && first.front() == '0') return {};
      ll a = atoll(first.data());
      if (a > INT_MAX) return {};

      string second;
      for (int j = i + 1; j < n; j++) {
        second.push_back(num[j]);
        if (second.size() > 1 && second.front() == '0') break;
        ll b = atoll(second.data());
        if (b > INT_MAX) break;
        if (a + b > INT_MAX) break;

        if (check(a, b, j + 1)) {
          return ans;
        }
      }
    }
    return {};
  }
};
