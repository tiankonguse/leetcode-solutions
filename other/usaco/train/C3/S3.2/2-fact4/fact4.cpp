/*
ID: tiankonguse
TASK: fact4
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fact4"

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

ll N;

ll twoLoop[] = {6, 2, 4, 8, 6, 2, 4, 8};
void Solver() {  //
  scanf("%lld", &N);
  ll fiveNum = 0;
  ll twoNum = 0;
  ll lastVal = 1;
  for (ll i = 1; i <= N; i++) {
    ll v = i;
    while (v % 2 == 0) {
      twoNum++;
      v /= 2;
    }
    while (v % 5 == 0) {
      fiveNum++;
      v /= 5;
    }
    lastVal = (lastVal * v) % 10;
  }
  ll leftTwoNum = twoNum - fiveNum;
  if (leftTwoNum > 0) {
    leftTwoNum = leftTwoNum % 4;
    lastVal = (lastVal * twoLoop[leftTwoNum]) % 10;
  }
  printf("%lld\n", lastVal);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/