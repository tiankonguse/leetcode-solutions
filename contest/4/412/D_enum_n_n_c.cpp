// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
int aa[6], an;
int bb[6], bn;
bool CheckEx(int i, int j) { return aa[i] == bb[j] && aa[j] == bb[i]; }

inline void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

bool CheckNum() {
  if (an <= 1 || an >= 5) return false;
  if (an == 2 || an == 3) {
    return true;
  }
  // == 4
  for (int i = 1; i < 4; i++) {
    swap(&aa[1], &aa[i]);
    swap(&bb[1], &bb[i]);
    if (CheckEx(0, 1) && CheckEx(2, 3)) {
      return true;
    }
    swap(&aa[1], &aa[i]);
    swap(&bb[1], &bb[i]);
  }
  return false;
}
bool Check(int a, int b) {
  if (a == b) return true;

  an = 0;
  bn = 0;
  while (a > 0 || b > 0) {
    if ((a % 10) != (b % 10)) {
      aa[an++] = a % 10;
      bb[bn++] = b % 10;
      if (an == 4) {
        if (!CheckNum()) {
          return false;
        }
      }
      if (an == 5) {
        return false;
      }
    }
    a = a / 10;
    b = b / 10;
  }
  return CheckNum();
}

ll Hash(int v) {
  ll bits[10] = {0};
  while (v) {
    bits[v % 10]++;
    v /= 10;
  }
  ll h = 0;
  for (int i = 1; i <= 9; i++) {
    int v = bits[i];
    while (v--) {
      h = h * 10 + i;
    }
  }
  return h;
}
ll h[5001];
int countPairs(int *nums, int numsSize) {
  int ans = 0;
  int n = numsSize;

  for (int i = 0; i < n; i++) {
    h[i] = Hash(nums[i]);
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (h[i] == h[j] && Check(nums[i], nums[j])) {
        ans++;
        continue;
      }
    }
  }

  return ans;
}