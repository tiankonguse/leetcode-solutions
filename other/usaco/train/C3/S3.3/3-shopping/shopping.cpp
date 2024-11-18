/*
ID: tiankonguse
TASK: shopping
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "shopping"

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

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

int s;
vector<int> specialPrice;
vector<vector<pair<int, int>>> specialOffers;
unordered_map<int, int> buys;
unordered_map<int, int> prices;
vector<int> products;

bool SpecialCheck(int i) {
  int n = specialOffers[i].size();
  for (int j = 0; j < n; j++) {
    auto [c, k] = specialOffers[i][j];
    if (!buys.count(c)) {
      return false;
    }
    if (k > buys[c]) {
      return false;
    }
  }
  return true;
}

int ans = 0;
int dp[100][6][6][6][6][6];

void Update(int cost) {  //
  ans = min(ans, cost);
}

int CalForceLeft() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    int ci = products[i];
    sum += buys[ci] * prices[ci];
  }
  return sum;
}

bool TrySelect(int si, int k) {
  for (auto [ci, ki] : specialOffers[si]) {
    if (ki * k > buys[ci]) {
      return false;
    }
  }
  return true;
}

int Dfs(int si, int cost) {
  if (si < 0) {
    ll tmp = CalForceLeft();
    Update(tmp + cost);
    return tmp;
  }
  int& k0 = buys[products[0]];
  int& k1 = buys[products[1]];
  int& k2 = buys[products[2]];
  int& k3 = buys[products[3]];
  int& k4 = buys[products[4]];
  int& ret = dp[si][k0][k1][k2][k3][k4];
  if (ret != -1) {
    Update(ret + cost);
    return ret;
  }
  ret = CalForceLeft();  // 不走折扣
  Update(ret + cost);

  // 不选择 si
  for (int k = 0; TrySelect(si, k); k++) {
    for (auto [ci, ki] : specialOffers[si]) {
      buys[ci] -= ki * k;
    }
    const int tmpCost = specialPrice[si] * k;
    ret = min(ret, tmpCost + Dfs(si - 1, cost + tmpCost));
    for (auto [ci, ki] : specialOffers[si]) {
      buys[ci] += ki * k;
    }
  }
  return ret;
}

void Solver() {  //
  scanf("%d", &s);
  specialOffers.resize(s);
  specialPrice.resize(s);
  for (int i = 0; i < s; i++) {
    int n;
    scanf("%d", &n);
    specialOffers[i].resize(n);
    for (int j = 0; j < n; j++) {
      scanf("%d%d", &specialOffers[i][j].first, &specialOffers[i][j].second);
    }
    scanf("%d", &specialPrice[i]);
  }

  int b;
  products.resize(5, 0);

  scanf("%d", &b);
  for (int i = 0; i < b; i++) {
    int c, k, p;
    scanf("%d%d", &c, &k);
    scanf("%d", &p);
    products[i] = c;
    buys[c] = k;
    prices[c] = p;
  }

  // 过滤掉无关的特价商品
  int si = 0;
  for (int i = 0; i < s; i++) {
    if (SpecialCheck(i)) {
      if (si < i) {
        specialOffers[si].swap(specialOffers[i]);
        specialPrice[si] = specialPrice[i];
      }
      si++;
    }
  }
  s = si;

  ans = CalForceLeft();
  memset(dp, -1, sizeof(dp));
  Dfs(s - 1, 0);
  printf("%d\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/