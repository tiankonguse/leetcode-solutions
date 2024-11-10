#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

struct Point {
  double x, y;
};

struct Square {
  Point leftBottom;
  double side;
  Point center;

  void Init(const vector<int>& s) {
    leftBottom = {double(s[0]), double(s[1])};
    side = s[2];
    center = {double(s[0]) + side / 2, double(s[1]) + side / 2};
  }
};

class Solution {
  Square s1, s2;

 public:
  vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
    s1.Init(square1);
    s2.Init(square2);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<int> square1, vector<int> square2, const vector<double>& ans) {
  TEST_SMP2(Solution, cutSquares, ans, square1, square2);
}

int main() {
  Test({-1, -1, 2}, {0, -1, 2}, {-1, 0, 2, 0});
  return 0;
}

#endif