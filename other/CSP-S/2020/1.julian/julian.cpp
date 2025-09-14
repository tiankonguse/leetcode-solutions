/*
ID: tiankonguse
TASK: julian
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7075
PATH:  P7075 [CSP-S2020] 儒略日
submission:
*/
#define TASK "julian"
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

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "3"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

map<ll, ll> mp;
const ll D365 = 365;
const ll Y1582 = 1582;
const ll Y400 = 365 * 400 + 400 / 4 - 400 / 100 + 400 / 400;
const ll normalMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const ll leapMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const ll M12 = 12;
vector<pair<ll, ll>> yearNormal;
vector<pair<ll, ll>> yearLeap;
vector<pair<ll, ll>> year1582;
vector<ll> offfsetDayY400;
ll p = -4713 + 1;
ll day = 0;
void InitYear() {
  yearNormal.reserve(366);
  yearLeap.reserve(366);
  year1582.reserve(366);
  for (int m = 0; m < M12; m++) {
    for (int d = 1; d <= normalMonth[m]; d++) {
      yearNormal.push_back({m + 1, d});
    }
  }
  for (int m = 0; m < M12; m++) {
    for (int d = 1; d <= leapMonth[m]; d++) {
      yearLeap.push_back({m + 1, d});
    }
  }
  for (int m = 0; m < M12; m++) {
    for (int d = 1; d <= normalMonth[m]; d++) {
      if (m + 1 == 10 && d == 5) {
        d = 15;  // 10月5日~10月14日不存在
      }
      year1582.push_back({m + 1, d});
    }
  }
  offfsetDayY400.reserve(400);
  ll offsetDay = 0;
  for (int i = 0; i < 400; i++) {
    offfsetDayY400.push_back(offsetDay);
    offsetDay += D365;
    if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0)) {
      offsetDay++;
    }
  }
}

void Init() {
  while (p < Y1582) {  // -4712年 ~ 1581年
    ll oneDay = D365;
    if (p % 4 == 0) {
      oneDay++;
    }
    mp[day] = p;  // p 年1月1日，是第 day 天
    day += oneDay;
    p++;
  }

  mp[day] = p;       // 1582 年 1 月 1 日，是第 day 天
  day += D365 - 10;  // 有 10 天不存在
  p++;
  while (p < 1600) {  // 1583 年 ~ 1599 年
    ll oneDay = D365;
    if (p % 400 == 0 || (p % 4 == 0 && p % 100 != 0)) {
      oneDay++;
    }
    mp[day] = p;  // p 年1月1日，是第 day 天
    day += oneDay;
    p++;
  }
  InitYear();
}

tuple<ll, ll, ll> Solver(ll r) {
  if (r < day) {  // 1600 年之内的，需要二分查找
    auto it = mp.upper_bound(r);
    it--;
    auto [itDay, itYear] = *it;
    if (itYear < Y1582) {
      ll leftDay = r - itDay;
      const vector<pair<ll, ll>>& yearDay = (itYear % 4 != 0) ? yearNormal : yearLeap;
      auto [month, day] = yearDay[leftDay];
      return make_tuple(itYear, month, day);
    } else if (itYear == Y1582) {
      ll leftDay = r - itDay;
      const vector<pair<ll, ll>>& yearDay = year1582;
      auto [month, day] = yearDay[leftDay];
      return make_tuple(itYear, month, day);
    } else {
      ll leftDay = r - itDay;
      const vector<pair<ll, ll>>& yearDay =
          (itYear % 400 == 0 || (itYear % 4 == 0 && itYear % 100 != 0)) ? yearLeap : yearNormal;
      auto [month, day] = yearDay[leftDay];
      return make_tuple(itYear, month, day);
    }
  } else {
    ll leftDay = r - day;
    ll itYear = p;
    if (leftDay > Y400) {
      ll num = leftDay / Y400;
      itYear += num * 400;
      leftDay -= num * Y400;
    }
    auto it = upper_bound(offfsetDayY400.begin(), offfsetDayY400.end(), leftDay);
    it--;
    ll yearNum = it - offfsetDayY400.begin();
    itYear += yearNum;
    leftDay -= *it;
    const vector<pair<ll, ll>>& yearDay =
        (itYear % 400 == 0 || (itYear % 4 == 0 && itYear % 100 != 0)) ? yearLeap : yearNormal;
    auto [month, day] = yearDay[leftDay];
    return make_tuple(itYear, month, day);
  }
}
void Solver() {  //
  Init();
  ll q, r;
  scanf("%lld", &q);
  while (q--) {
    scanf("%lld", &r);
    auto [Y, M, D] = Solver(r);
    if (Y <= 0) {
      Y--;
      Y = -Y;
      printf("%lld %lld %lld BC\n", D, M, Y);
    } else {
      printf("%lld %lld %lld\n", D, M, Y);
    }
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/