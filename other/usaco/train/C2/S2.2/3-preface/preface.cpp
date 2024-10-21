/*
ID: tiankonguse
TASK: preface
LANG: C++
*/
#define TASK "preface"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

map<char, ll> h;

string buf;
void Add(char c) {
  //   buf.push_back(c);
  h[c]++;
}

void Solver(ll n, char v10, char v5, char v1) {
  if (n >= 9) {  // 9  v10 - v1
    Add(v1);
    Add(v10);
  } else if (n >= 5) {  // 8 7 6 5 v5 + v1
    Add(v5);
    while (n > 5) {
      Add(v1);
      n--;
    }
  } else if (n == 4) {  // 4 v5 - v1
    Add(v1);
    Add(v5);
  } else {  // 3 2 1 v1
    while (n > 0) {
      Add(v1);
      n--;
    }
  }
}

void Solver(int n) {
  Solver(n / 1000, ' ', ' ', 'M');
  n %= 1000;

  Solver(n / 100, 'M', 'D', 'C');
  n %= 100;

  Solver(n / 10, 'C', 'L', 'X');
  n %= 10;

  Solver(n, 'X', 'V', 'I');
}
void Solver() {  //
  ll n;
  scanf("%lld", &n);
  for (ll i = 1; i <= n; i++) {
    buf.clear();
    Solver(i);
    // printf("i=%lld %s\n", i, buf.c_str());
  }
  const string order = "IVXLCDM";
  for (char c : order) {
    ll k = h[c];
    if (k > 0) {
      printf("%c %lld\n", c, k);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
 --------------------------
20
----- our output ---------
I_28
V_10
X_14

------ Data for Run 3 [length=4 bytes] ------
100
----- our output ---------
I_140
V_50
X_150
L_50
C_11


*/