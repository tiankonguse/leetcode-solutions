// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  char kthCharacter(int k) {
    string now = "a";
    while (now.size() < k) {
      int n = now.size();
      now.append(now);
      for (int i = n; i < now.size(); i++) {
        int v = (now[i] - 'a' + 1) % 26;
        now[i] = 'a' + v;
      }
    }
    myprintf("now=%s\n", now.c_str());
    return now[k - 1];
  }
};