// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
typedef long long ll;
class ExamRoom {
  unordered_map<int, int> m;
  map<int, set<pair<int, int>>> dis;
  int n;

  void Add(int a, int b) {
    if (a > b) return;

    m[a] = b;
    m[b] = a;

    int len = b - a;

    if (a == 0 || b == n) {
      dis[len].insert({a, b});
    } else {
      dis[len / 2].insert({a, b});
    }
  }
  void Erase(int a, int b) {
    m.erase(a);
    m.erase(b);
    int len = b - a;
    if (a != 0 && b != n) {
      len = len / 2;
    }

    dis[len].erase({a, b});
    if (dis[len].size() == 0) {
      dis.erase(len);
    }
  }

 public:
  ExamRoom(int n) {
    n--;
    this->n = n;
    Add(0, n);
  }

  int seat() {
    auto [a, b] = *dis.rbegin()->second.begin();
    Erase(a, b);

    int ans = -1;
    if (a == 0) {
      ans = 0;
      Add(a + 1, b);
    } else if (b == n) {
      ans = n;
      Add(a, b - 1);
    } else {
      ans = (a + b) / 2;
      Add(a, ans - 1);
      Add(ans + 1, b);
    }
    return ans;
  }

  void leave(int p) {
    int a = p, b = p;
    if (m.count(p - 1)) {
      int x = m[p - 1], y = p - 1;
      Erase(x, y);
      a = x;
    }
    if (m.count(p + 1)) {
      int x = p + 1, y = m[p + 1];
      Erase(x, y);
      b = y;
    }
    Add(a, b);
  }
};
