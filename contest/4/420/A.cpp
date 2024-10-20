// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  vector<string> stringSequence(const string& target) {
    ll sum = 0;
    for (auto c : target) {
      sum += c - 'a' + 1;
    }
    vector<string> ans;
    ans.reserve(sum);
    string buf;
    buf.reserve(target.size());
    for (auto c : target) {
      buf.push_back('a');
      ans.push_back(buf);
      while (buf.back() < c) {
        buf.back()++;
        ans.push_back(buf);
      }
    }

    return ans;
  }
};