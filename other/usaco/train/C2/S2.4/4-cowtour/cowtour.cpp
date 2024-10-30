/*
ID: tiankonguse
TASK: cowtour
LANG: C++

warning: this program uses gets(), which is unsafe.

gets is unsafe because you give it a buffer, but you don't tell it how big the
buffer is. The input may write past the end of the buffer, blowing up your
program fairly spectacularly. Using fgets instead is a bit better because you
tell it how big the buffer is, like this:

const int bufsize = 4096;
char buffer[bufsize];
fgets(buffer, bufsize, stdin);
https://stackoverflow.com/questions/2973985/why-gets-is-not-working
*/
#define TASK "cowtour"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n;
vector<pair<double, double>> points;
vector<vector<double>> nums;
char str[155][155];

double Dis(int i, int j) {
  auto [x0, y0] = points[i];
  auto [x1, y1] = points[j];
  return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}
vector<double> maxDis;
double baseMaxDis;
void Solver() {  //
  scanf("%lld", &n);
  points.resize(n);
  nums.resize(n, vector<double>(n, INF));
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &points[i].first, &points[i].second);
  }
  for (int i = 0; i < n; i++) {
    scanf("%s", str[i]);
  }
  for (int i = 0; i < n; i++) {
    nums[i][i] = 0;
    for (int j = i + 1; j < n; j++) {
      if (str[i][j] == '0') continue;
      double d = Dis(i, j);
      nums[i][j] = d;
      nums[j][i] = d;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        nums[i][j] = min(nums[i][j], nums[i][k] + nums[k][j]);
      }
    }
  }

  baseMaxDis = 0;
  maxDis.resize(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double& v = nums[i][j];
      if (abs(v - INF) < eps) {
        v = -1;
      }
      maxDis[i] = max(maxDis[i], v);
      baseMaxDis = max(baseMaxDis, maxDis[i]);
      //   printf("%+3.6f ", v);
    }
    // printf("\n");
  }

  double ans = INF;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (nums[i][j] > 0) continue;
      double d = Dis(i, j);
      double tmpAns = max(maxDis[i] + maxDis[j] + d, baseMaxDis);
      ans = min(ans, tmpAns);
    }
  }
  printf("%.6f\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/