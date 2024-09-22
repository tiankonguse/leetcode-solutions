// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
    unordered_set<string> h(bannedWords.begin(), bannedWords.end());
    int num = 0;
    for (auto& w : message) {
      if (h.count(w)) {
        num++;
      }
    }
    return num >= 2;
  }
};