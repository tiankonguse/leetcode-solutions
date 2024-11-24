/*
ID: tiankonguse
TASK: buylow
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "buylow"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
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

struct BigNum {
 public:
  BigNum(const int val = 0) { bits.push_back(val); }
  vector<int> bits;
  int Len() const { return bits.size(); }
  int Get(const int offset) const {
    if (offset < int(bits.size())) {
      return bits[offset];
    }
    return 0;
  }
  void Set(const int offset, const int val) {
    while (offset >= int(bits.size())) {
      bits.push_back(0);
    }
    bits[offset] = val;
  }
  void Push(const int val) { bits.push_back(val); }
  void init(int n) {
    bits.clear();
    bits.resize(n, 0);
  }
  BigNum& operator+=(const BigNum& b) {  //
    BigNum& a = *this;
    int n = max(a.Len(), b.Len());
    int carry = 0;
    for (int i = 0; i < n; i++) {
      const int v = a.Get(i) + b.Get(i) + carry;
      a.Set(i, v % 10);
      carry = v / 10;
    }
    while (carry) {
      a.Push(carry % 10);
      carry /= 10;
    }
    return a;
  }
  void Output() {
    for (int i = bits.size() - 1; i >= 0; i--) {
      printf("%d", bits[i]);
    }
  }
};

ll n;
vector<ll> nums;
vector<pair<ll, BigNum>> dp;

void Solver() {  //
  scanf("%lld", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }

  dp.resize(n);
  unordered_set<ll> flag;
  for (ll i = 0; i < n; i++) {
    dp[i] = {1, BigNum(1)};
    flag.clear();
    // printf("\ni=%lld v=%lld\n", i, nums[i]);
    for (ll j = i - 1; j >= 0; j--) {
      if (nums[j] <= nums[i]) continue;

      if (dp[j].first + 1 > dp[i].first) {
        dp[i] = {dp[j].first + 1, dp[j].second};
        // printf("more biger: j=%lld v=%lld %lld->", j, nums[j], dp[j].first);
        // dp[j].second.Output();
        // printf("\n");
        flag.clear();
        flag.insert(nums[j]);
      } else if (dp[j].first + 1 == dp[i].first) {
        // printf("eq: j=%lld v=%lld %lld->", j, nums[j], dp[j].first);
        // dp[j].second.Output();
        // printf("\n");
        if (flag.count(nums[j]) == 0) {
          flag.insert(nums[j]);
          dp[i].second += dp[j].second;
        }
      }
    }
  }

  pair<ll, BigNum> ans(0, BigNum(0));
  flag.clear();
  for (ll i = n - 1; i >= 0; i--) {
    // printf("i=%lld v=%lld maxLen=%lld maxNum=", i, nums[i], dp[i].first);
    // dp[i].second.Output();
    // printf("\n");
    if (dp[i].first > ans.first) {
      ans = dp[i];
      flag.clear();
      flag.insert(nums[i]);
    } else if (dp[i].first == ans.first) {
      if (flag.count(nums[i]) == 0) {
        flag.insert(nums[i]);
        ans.second += dp[i].second;
      }
    }
  }

  printf("%lld ", ans.first);
  ans.second.Output();
  printf("\n");
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.007 secs limit:1s, 1692 KB]
   Test 2: TEST OK [0.007 secs limit:1s, 1740 KB]
   Test 3: TEST OK [0.004 secs limit:1s, 1632 KB]
   Test 4: TEST OK [0.004 secs limit:1s, 1736 KB]
   Test 5: TEST OK [0.007 secs limit:1s, 1732 KB]
   Test 6: TEST OK [0.018 secs limit:1s, 1596 KB]
   Test 7: TEST OK [0.014 secs limit:1s, 1632 KB]
   Test 8: TEST OK [0.007 secs limit:1s, 1692 KB]
   Test 9: TEST OK [0.049 secs limit:1s, 3656 KB]
   Test 10: TEST OK [0.315 secs limit:1s, 3268 KB]
*/