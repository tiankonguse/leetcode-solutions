// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  int maximumScore1(int a, int b, int c) {
    max_queue<int> que;
    que.push(a);
    que.push(b);
    que.push(c);

    int ans = 0;
    while (que.size() >= 2) {
      a = que.top();
      que.pop();
      b = que.top();
      que.pop();
      a--;
      b--;
      ans++;
      if (a > 0) que.push(a);
      if (b > 0) que.push(b);
    }

    return ans;
  }
  int maximumScore(int a, int b, int c) {
    if (a < b) swap(a, b);
    if (a < c) swap(a, c);
    if (a >= b + c) {
      return b + c;
    } else {
      return (a + b + c) / 2;
    }
  }
};
