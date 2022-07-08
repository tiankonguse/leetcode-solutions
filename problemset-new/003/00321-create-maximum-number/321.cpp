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

class Solution {
  vector<int> ans;

  void getMaxSeq(vector<int>& nums, vector<int>& buf, int k) {
    buf.clear();
    buf.reserve(k);

    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int v = nums[i];
      int leftNum = n - 1 - i;
      while (!buf.empty() && buf.size() + 1 + leftNum > k && buf.back() < v) {
        buf.pop_back();
      }
      if (buf.size() < k) {
        buf.push_back(v);
      }
    }
  }

  void MergeSeq(vector<int>& buf1, vector<int>& buf2, vector<int>& buf) {
    int n1 = buf1.size();
    int n2 = buf2.size();

    buf.clear();
    buf.reserve(n1 + n2);

    int p1 = 0, p2 = 0;

    while (p1 < n1 && p2 < n2) {
      if (buf1[p1] < buf2[p2]) {
        buf.push_back(buf2[p2]);
        p2++;
      } else if (buf1[p1] > buf2[p2]) {
        buf.push_back(buf1[p1]);
        p1++;
      } else {
        int pp1 = p1;
        int pp2 = p2;
        while (pp1 < n1 && pp2 < n2 && buf1[pp1] == buf2[pp2]) {
          pp1++;
          pp2++;
        }
        if (pp1 == n1) {
          buf.push_back(buf2[p2]);
          p2++;
        } else if (pp2 == n2) {
          buf.push_back(buf1[p1]);
          p1++;
        } else if (buf1[pp1] > buf2[pp2]) {
          buf.push_back(buf1[p1]);
          p1++;
        } else {
          buf.push_back(buf2[p2]);
          p2++;
        }
      }
    }

    while (p1 < n1) {
      buf.push_back(buf1[p1]);
      p1++;
    }

    while (p2 < n2) {
      buf.push_back(buf2[p2]);
      p2++;
    }
  }

  void Update(vector<int>& buf) {
    int n = buf.size();
    // printf("update buf:");
    // for (int i = 0; i < n; i++) {
    //   printf("%d ", buf[i]);
    // }
    // printf("\n");

    for (int i = 0; i < n; i++) {
      if (buf[i] == ans[i]) continue;
      if (buf[i] < ans[i]) return;
      if (buf[i] > ans[i]) {
        while (i < n) {  // 更优，替换 ans
          ans[i] = buf[i];
          i++;
        }
      }
    }
  }

 public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<int> buf1, buf2, buf3;
    ans.resize(k, 0);
    for (int i = 0; i <= k; i++) {
      int l = i;
      int r = k - i;
      if (l > nums1.size() || r > nums2.size()) continue;

      //   printf("1 i=%d\n", i);
      getMaxSeq(nums1, buf1, l);
      // printf("buf1:");
      // for (int i = 0; i < l; i++) {
      //   printf("%d ", buf1[i]);
      // }
      // printf("\n");
      //   printf("2 l=%d buf1=%d\n", l, buf1.size());
      getMaxSeq(nums2, buf2, r);
      // printf("buf2:");
      // for (int i = 0; i < r; i++) {
      //   printf("%d ", buf2[i]);
      // }
      // printf("\n");
      //   printf("3 r=%d buf2=%d\n", r, buf2.size());

      MergeSeq(buf1, buf2, buf3);
      //   printf("4  i=%d k=%d buf3=%d\n", i, k, buf3.size());
      Update(buf3);
      //   printf("5  i=%d\n", i);
    }
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
