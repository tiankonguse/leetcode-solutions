/*
ID: tiankonguse
TASK: palsquare
LANG: C++
*/
#define TASK "palsquare"

#include <bits/stdc++.h>

using namespace std;

bool Check(int v, const int b) {  //
  vector<int> bits;
  while (v) {
    bits.push_back(v % b);
    v /= b;
  }
  int n = bits.size();
  for (int i = 0; i < n; i++) {
    if (bits[i] != bits[n - 1 - i]) {
      return false;
    }
  }
  return true;
}

string ToString(int v, const int b) {
  string str;
  while (v) {
    int vv = v % b;
    if (vv < 10) {
      str.push_back('0' + vv);
    } else {
      str.push_back('A' + (vv - 10));
    }
    v /= b;
  }
  std::reverse(str.begin(), str.end());
  return str;
}

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
void Solver() {  //
  int B;
  scanf("%d", &B);
  for (int i = 1; i <= 300; i++) {
    if (Check(i * i, B)) {
      printf("%s %s\n", ToString(i, B).c_str(), ToString(i * i, B).c_str());
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
