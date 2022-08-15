#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef __int128_t int128;

typedef vector<int> vi;
typedef vector<vi> vvi;

typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;

typedef long double ld;
typedef vector<ld> vld;

typedef vector<bool> vb;
typedef vector<string> vs;

// const int mod = 1e9 + 7;

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define rep1(i, n) for (ll i = 1; i <= (n); i++)
#define rrep(i, n) for (ll i = (n)-1; i >= 0; i--)
#define rrep1(i, n) for (ll i = (n); i >= 1; i--)
#define all(v) (v).begin(), (v).end()
#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define sz(x) (int)(x).size()
#define SZ(A) int((A).size())
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define CTN(T, x) (T.find(x) != T.end())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define fi first
#define se second

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
inline void RST(T& A) {
  memset(A, 0, sizeof(A));
}
template <class T>
inline void FLC(T& A, int x) {
  memset(A, x, sizeof(A));
}
template <class T>
inline void CLR(T& A) {
  A.clear();
}
template <class T>
T& chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
  return a;
}
template <class T>
T& chmax(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = max(a, b);
  }
  return a;
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// LONG_MIN(10进制 10位), LONG_MAX(10进制 19位)

/*
unordered_map / unordered_set

lower_bound 大于等于
upper_bound 大于
reserve 预先分配内存
reverse(all(vec)) 反转
sum = accumulate(a.begin(), a.end(), 0ll);
__builtin_popcount 一的个数
vector / array : upper_bound(all(vec), v)
map: m.upper_bound(v)

区间个数： std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

vector 去重
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());

size_t found=str.find(string/char/char*);
std::string::npos

排序，小于是升序：[](auto&a, auto&b){ return a < b; })
优先队列 priority_queue<Node>：top/pop/push/empty
struct Node {
  Node(int t = 0) : t(t) {}
  int t;
  // 小于是最大堆，大于是最小堆
  bool operator<(const Node& that) const { return this->t < that.t; }
};

srand((unsigned)time(NULL));
rand();

mt19937 gen{random_device{}()};
uniform_real_distribution<double> dis(min, max);
function<double(void)> Rand = [that = this]() { return that->dis(that->gen); };

*/

const int N = 3 * 3 * 3 * 3 * 3;
int dp[30][7][7][N];
struct StInfo {
  int now[6], a, b;
};
StInfo hashDecode[N];
int pow3[N];

class Solution {
  int M, maxM;
  void decode(int bit, int now[6], int& aNow, int& bNow) {
    int index = 0;
    memset(now, 0, sizeof(int) * 6);
    aNow = bNow = 0;
    while (bit) {
      now[index] = bit % 3;
      if (now[index] == 1) {
        aNow++;
      } else if (now[index] == 2) {
        bNow++;
      }
      index++;
      bit /= 3;
    }
  }

 public:
  int getMaxGridHappiness(int n, int m, int A, int B) {
    if (n < m) {
      swap(n, m);
    }

    M = m;
    maxM = 1;
    pow3[0] = 1;
    for (int i = 1; i <= M; i++) {
      maxM *= 3;
      pow3[i] = maxM;
    }
    for (int i = 0; i < maxM; i++) {
      decode(i, hashDecode[i].now, hashDecode[i].a, hashDecode[i].b);
    }
    int nm = n * m;
    int selfScore[3] = {0, 120, 40};
    int otherScore[3][3] = {
        {0, 0, 0},      //
        {0, -60, -10},  //
        {0, -10, 40}    //
    };

    for (int i = 0; i < nm; i++) {
      int x = i / m;
      int y = i % m;
      for (int a = 0; a <= A; a++) {
        for (int b = 0; b <= B; b++) {
          for (int k = 0; k < maxM; k++) {
            int aNow = hashDecode[k].a;
            int bNow = hashDecode[k].b;
            int* now = hashDecode[k].now;
            if (aNow > a || bNow > b) continue;

            int midab[3] = {2, a, b};
            int nowAns = 0;

            if (x == 0) {  //第一行
              if (k >= pow3[y + 1]) continue;
              int v = now[y];
              int prek = k % pow3[y];
              midab[v]--;
              int prea = midab[1], preb = midab[2];

              int tmp = selfScore[v];  // self
              if (y > 0) {
                tmp += dp[i - 1][prea][preb][prek];
                tmp += otherScore[v][now[y - 1]];  // 左右
              }
              nowAns = tmp;

            } else {
              int v = now[m - 1];
              int midk = k % pow3[m - 1];
              midab[v]--;

              for (int j = 0; j <= 2; j++) {
                int prek = midk * 3 + j;
                int prea = midab[1], preb = midab[2];
                if (hashDecode[prek].a > prea || hashDecode[prek].b > preb) {
                  continue;
                }

                int tmp = dp[i - 1][prea][preb][prek];
                tmp += selfScore[v];      // self
                tmp += otherScore[v][j];  //上下
                if (y > 0) {
                  tmp += otherScore[v][now[m - 2]];  // 左右
                }
                nowAns = max(nowAns, tmp);
              }
            }

            dp[i][a][b][k] = nowAns;

            // printf("i=%d a=%d b=%d k=%d nowAns=%d\n", i, a, b, k, nowAns);
          }
        }
      }
    }

    int ans = ninf;
    for (int i = 0; i < maxM; i++) {
      int tmp = dp[nm - 1][A][B][i];
      ans = max(ans, tmp);
    }

    // n >= m
    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
