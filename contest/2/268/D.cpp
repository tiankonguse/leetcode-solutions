#include "base.h"

#define myprintf(format, args...) printf("line[%d]" format, __LINE__, ##args)
#define myprintf(format, args...)

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
// int dir[8][2] = {{0,1},{1, 1},{1,0},{1,-1}, {0,-1}, {-1, -1}, {-1,0}, {-1,
// 1}}; lower_bound 大于等于 upper_bound 大于 vector/array:
// upper_bound(vec.begin(), vec.end(), v) map: m.upper_bound(v) reserve
// vector预先分配内存 reverse(v.begin(), v.end()) 反转 sum =
// accumulate(a.begin(), a.end(), 0); unordered_map / unordered_set
// __builtin_popcount 一的个数
// size_t found=str.find(char/char*/string); std::string::npos
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

// mutex mtx;       // 互斥量，锁，定义一个即可
// condition_variable cv; // 条件变量
// cv.notify_one(); // 事件通知
// unique_lock<mutex> lck(mtx);
// cv.wait(lck); //等待事件

// atomic_int tick; // 原子计数
// this_thread::yield();  // 线程 sleep

// #include <semaphore.h> // 需要手动包含信号量头文件
// sem_t sem_done;
// sem_init(&bar_done, 0 , 1);
// sem_wait(&bar_done);
// sem_post(&foo_done);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;

ll table[10][31] = {
    {1LL,       3LL,       5LL,        7LL,         9LL,         33LL,
     99LL,      313LL,     585LL,      717LL,       7447LL,      9009LL,
     15351LL,   32223LL,   39993LL,    53235LL,     53835LL,     73737LL,
     585585LL,  1758571LL, 1934391LL,  1979791LL,   3129213LL,   5071705LL,
     5259525LL, 5841485LL, 13500531LL, 719848917LL, 910373019LL, 939474939LL},
    {1LL,       2LL,       4LL,       8LL,       121LL,      151LL,
     212LL,     242LL,     484LL,     656LL,     757LL,      29092LL,
     48884LL,   74647LL,   75457LL,   76267LL,   92929LL,    93739LL,
     848848LL,  1521251LL, 2985892LL, 4022204LL, 4219124LL,  4251524LL,
     4287824LL, 5737375LL, 7875787LL, 7949497LL, 27711772LL, 83155138LL},
    {1LL,       2LL,       3LL,        5LL,         55LL,        373LL,
     393LL,     666LL,     787LL,      939LL,       7997LL,      53235LL,
     55255LL,   55655LL,   57675LL,    506605LL,    1801081LL,   2215122LL,
     3826283LL, 3866683LL, 5051505LL,  5226225LL,   5259525LL,   5297925LL,
     5614165LL, 5679765LL, 53822835LL, 623010326LL, 954656459LL, 51717171715LL},
    {1LL,          2LL,          3LL,          4LL,           6LL,
     88LL,         252LL,        282LL,        626LL,         676LL,
     1221LL,       15751LL,      18881LL,      10088001LL,    10400401LL,
     27711772LL,   30322303LL,   47633674LL,   65977956LL,    808656808LL,
     831333138LL,  831868138LL,  836131638LL,  836181638LL,   2512882152LL,
     2596886952LL, 2893553982LL, 6761551676LL, 12114741121LL, 12185058121LL},
    {1LL,       2LL,       3LL,       4LL,       5LL,       7LL,
     55LL,      111LL,     141LL,     191LL,     343LL,     434LL,
     777LL,     868LL,     1441LL,    7667LL,    7777LL,    22022LL,
     39893LL,   74647LL,   168861LL,  808808LL,  909909LL,  1867681LL,
     3097903LL, 4232324LL, 4265624LL, 4298924LL, 4516154LL, 4565654LL},
    {1LL,           2LL,           3LL,           4LL,           5LL,
     6LL,           8LL,           121LL,         171LL,         242LL,
     292LL,         16561LL,       65656LL,       2137312LL,     4602064LL,
     6597956LL,     6958596LL,     9470749LL,     61255216LL,    230474032LL,
     466828664LL,   485494584LL,   638828836LL,   657494756LL,   858474858LL,
     25699499652LL, 40130703104LL, 45862226854LL, 61454945416LL, 64454545446LL},
    {1LL,      2LL,       3LL,       4LL,       5LL,       6LL,
     7LL,      9LL,       121LL,     292LL,     333LL,     373LL,
     414LL,    585LL,     3663LL,    8778LL,    13131LL,   13331LL,
     26462LL,  26662LL,   30103LL,   30303LL,   207702LL,  628826LL,
     660066LL, 1496941LL, 1935391LL, 1970791LL, 4198914LL, 55366355LL},
    {1LL,       2LL,       3LL,       4LL,       5LL,       6LL,
     7LL,       8LL,       191LL,     282LL,     373LL,     464LL,
     555LL,     646LL,     656LL,     6886LL,    25752LL,   27472LL,
     42324LL,   50605LL,   626626LL,  1540451LL, 1713171LL, 1721271LL,
     1828281LL, 1877781LL, 1885881LL, 2401042LL, 2434342LL, 2442442LL}};

class Solution {
  ll Pow(int k, int l) {
    ll base = 10;
    ll ans = 1;

    while (l) {
      ans *= base;
      l--;
    }

    return ans;
  }
  bool IsMirror(ll v, int k) {
    int buf[65];
    int n = 0;
    while (v) {
      buf[n++] = v % k;
      v /= k;
    }

    for (int i = 0; i < n; i++, n--) {
      if (buf[i] != buf[n - 1]) return false;
    }
    return true;
  }
  ll CalVal(int l, int v) {
    string preBuf = std::to_string(v);
    string subBuf = preBuf;
    reverse(subBuf.begin(), subBuf.end());
    if (preBuf.size() + subBuf.size() > l) {
      preBuf.pop_back();
    }

    string buf = preBuf + subBuf;
    return atoll(buf.c_str());
  }

  void Cal2(int k, vector<ll>& table) {
    // printf("k=%d:", k);
    for (int l = 1; table.size() < 30; l++) {
      int preLen = (l + 1) / 2;
      ll preMax = Pow(10, preLen);
      ll preMin = preMax / 10;
      for (ll i = preMin; table.size() < 30 && i < preMax; i++) {
        ll val = CalVal(l, i);
        if (IsMirror(val, 10) && IsMirror(val, k)) {
          table.push_back(val);
          // printf("%lld,", val);
        }
      }
    }
    // printf("\n");
  }
  void Init() {
    vector<vector<ll>> tables;
    tables.resize(10);
    for (int i = 2; i <= 9; i++) {
      Cal2(i, tables[i]);
    }
  }

 public:
  long long kMirror(int k, int n) {
    ll ans = 0;

    for (int i = 0; i < n; i++) {
      ans += table[k - 2][i];
    }

    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
