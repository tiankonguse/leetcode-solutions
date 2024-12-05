/*
ID: tiankonguse
TASK: vans
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "vans"
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

/*
  0         0              1
  -         -        -     -
|
  -   =>    -  =>    -
                        |
  -         -        -
|
  -         -        -     -


  1     2     3           4         5
  -    ---   --       --         - --
|              |        |
|       --      --      |          --
|  =>  |   =>      =>   |   =>    |
|       --      --       --       |
|              |                  |
 --    ---   --       -- --      -


  2      2           5        4
---    ---        -----     ---
                               |
 --     --        -----      --
|   => |      =>         =>
 --     --        --         -----
                    |
---    ---       ---        ------

 3               1
--               -
  |            |
   --       --
      =>
   --       --
  |            |
--              --

     4          1         6
 --             -        -
   |          |         |
   |          |          -
   |   =>     |   =>
    --      --        ----

 -- --      -- --     ----

   5         1           7
- --       -----        --

  --       --           --
 |    =>     |   =>
 |           |          --
 |           |         |
-             --        --

     6          6          1
    -          -         ----
   |          |         |
    -          -         -
       =>          =>     |
 ----       ----      ----

 ----       ----      -------

   7        7         1
  --       --        -------

  --       --        --
      =>         =>    |
  --       --        --
 |        |         |
  --       --        ------
*/

vector<vector<int>> g;

unordered_set<int> S, T;

void Init() {
  g.resize(10);
  g[0] = {0, 1};
  g[1] = {2, 3, 4, 5};
  g[2] = {2, 4, 5};
  g[3] = {1};
  g[4] = {1, 6};
  g[5] = {1, 7};
  g[6] = {1, 6};
  g[7] = {1, 7};
  S = {0, 1};
  T = {1, 2};
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
    printf("\n");
  }
};
vector<vector<BigNum>> dp;
vector<vector<int>> flag;

BigNum Dfs(int p, int n) {
  auto& ret = dp[p][n];
  if (flag[p][n]) return ret;
  flag[p][n] = 1;
  ret = 0;
  if (n == 0) {
    return ret = T.count(p);
  }

  for (auto v : g[p]) {
    ret += Dfs(v, n - 1);
  }

  return ret;
}

void Solver(int n) {
  if (n == 1) {
    printf("0\n");
    return;
  }
  flag.resize(10, vector<int>(1010, 0));
  dp.resize(10, vector<BigNum>(1010));
  BigNum ans = 0;
  for (auto s : S) {
    ans += Dfs(s, n - 2);
  }
  ans += ans;
  ans.Output();
  return;
}

void Solver() {  //
  int n;
  Init();
  scanf("%d", &n);
  Solver(n);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Here are the test data inputs:

------- test 1 [length 2 bytes] ----
4
------- test 2 [length 2 bytes] ----
2
------- test 3 [length 2 bytes] ----
3
------- test 4 [length 2 bytes] ----
1
------- test 5 [length 3 bytes] ----
10
------- test 6 [length 3 bytes] ----
30
------- test 7 [length 3 bytes] ----
50
------- test 8 [length 4 bytes] ----
100
------- test 9 [length 4 bytes] ----
300
------- test 10 [length 4 bytes] ----
500
------- test 11 [length 5 bytes] ----
1000
*/