/*
ID: tiankonguse
TASK: ratios
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "ratios"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
#endif
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int p[4][3];
int N = 200;
int ans = INT_MAX;
int I, J, K, G;

void Update(int i, int j, int k) {
  int g[3] = {0, 0, 0};
  vector<int> rates;
  for (int x = 0; x < 3; x++) {
    g[x] = i * p[1][x] + j * p[2][x] + k * p[3][x];
    if (p[0][x] == 0) {
      continue;
    }
    if (g[x] % p[0][x] != 0) {
      // printf("i=%d j=%d k=%d x=%d %d%%%d=%d\n", i, j, k, x, g[x], p[0][x],
      //        g[x] % p[0][x]);
      return;
    }
    rates.push_back(g[x] / p[0][x]);
    if (rates.size() >= 2 && rates.back() != rates.front()) {
      // printf("i=%d j=%d k=%d x=%d %d != %d\n", i, j, k, x, g[x] / p[0][x],
      //        g[x - 1] / p[0][x - 1]);
      return;
    }
  }
  if (i + j + k > 0 && i + j + k < ans) {
    ans = i + j + k;
    I = i;
    J = j;
    K = k;
    G = rates.front();
  }
}

int Cal(int i) {
  for (int k = 0; k < 3; k++) {
    if (p[0][k] == 0 && p[i][k] != 0) {
      return 0;
    }
  }
  return N;
}

void Solver() {  //
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%d", &p[i][j]);
      printf("input[%d]\n", p[i][j]);
    }
  }
  // Update(8, 1, 5);
  int maxI = Cal(1);
  int maxJ = Cal(2);
  int maxK = Cal(3);
  for (int i = 0; i <= maxI; i++) {
    if (i > ans) break;
    for (int j = 0; j <= maxJ; j++) {
      if (i + j > ans) break;
      for (int k = 0; k <= maxK; k++) {
        if (i + j + k > ans) break;
        Update(i, j, k);
      }
    }
  }

  if (ans != INT_MAX) {
    printf("%d %d %d %d\n", I, J, K, G);
  } else {
    printf("NONE\n");
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/