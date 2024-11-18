/*
ID: tiankonguse
TASK: shopping
LANG: C++
MAC EOF: ctrl+D
algorithm: complete pack
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
unordered_map<int, int> indexs;
vector<int> products;
vector<int> nums;
vector<int> prices;

bool SpecialCheck(int i) {
  int n = specialOffers[i].size();
  for (int j = 0; j < n; j++) {
    auto [c, k] = specialOffers[i][j];
    if (!indexs.count(c)) {
      return false;
    }
    if (k > nums[indexs[c]]) {
      return false;
    }
  }
  return true;
}

int dp[6][6][6][6][6];

int CalForceLeft() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += nums[i] * prices[i];
  }
  return sum;
}

bool TrySelect(int si) {
  for (auto [ci, ki] : specialOffers[si]) {
    int index = indexs[ci];
    if (ki > nums[index]) {
      return false;
    }
  }
  return true;
}

const tuple<int, int, int, int, int> Trans(int si) {
  int K[5] = {0, 0, 0, 0, 0};  //
  for (auto [ci, ki] : specialOffers[si]) {
    K[indexs[ci]] = ki;
  }
  return {K[0], K[1], K[2], K[3], K[4]};
}

int& Ans() {
  int k0 = nums[0];
  int k1 = nums[1];
  int k2 = nums[2];
  int k3 = nums[3];
  int k4 = nums[4];
  return dp[k0][k1][k2][k3][k4];
}

int Dfs() {
  int& ret = Ans();
  if (ret != -1) {
    return ret;
  }

  ret = CalForceLeft();
  for (int si = 0; si < s; si++) {
    if (!TrySelect(si)) continue;

    for (auto [ci, ki] : specialOffers[si]) {
      nums[indexs[ci]] -= ki;
    }

    ret = min(ret, specialPrice[si] + Dfs());

    for (auto [ci, ki] : specialOffers[si]) {
      nums[indexs[ci]] += ki;
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
  nums.resize(5, 0);
  prices.resize(5, 0);

  scanf("%d", &b);
  for (int i = 0; i < b; i++) {
    int c, k, p;
    scanf("%d%d", &c, &k);
    scanf("%d", &p);
    products[i] = c;
    nums[i] = k;
    prices[i] = p;

    indexs[c] = i;
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

  memset(dp, -1, sizeof(dp));
  printf("%d\n", Dfs());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/