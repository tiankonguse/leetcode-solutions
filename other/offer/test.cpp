#include <iostream>

#include "bits/stdc++.h"
using namespace std;

vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int n = 9;
vector<int> lastRes;

void recursion(const int sum, const int index) {
  /* The end */
  if (index >= n) {
    /* TODO: compute the result */
    if (sum == 100) {
      printf("sum=%d ", sum);
      for (int i = 0; i < lastRes.size(); i += 2) {
        if (i == 0) {
          printf("%d", lastRes[i + 1]);
        } else {
          printf(" %c %d", lastRes[i] == 1 ? '+' : '-', lastRes[i + 1]);
        }
      }
      printf("\n");
    }
    return;
  }
  for (int len = 1; index + len <= n; ++len) {
    int tmp = 0;
    for (int j = 0; j < len; ++j) {
      tmp = tmp * 10 + nums[index + j];
    }

    // +
    lastRes.push_back(1);
    lastRes.push_back(tmp);
    recursion(sum + tmp, index + len);
    lastRes.pop_back();
    lastRes.pop_back();

    // -
    if (lastRes.size() > 0) {
      lastRes.push_back(-1);
      lastRes.push_back(tmp);
      recursion(sum - tmp, index + len);
      lastRes.pop_back();
      lastRes.pop_back();
    }
  }
  return;
}

int main() {
  recursion(0, 0);
  return 0;
}