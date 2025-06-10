
/*
ID: tiankonguse
TASK: tree
LANG: C++
CONTEST: CSP-S 2023
qoj: https://qoj.ac/contest/1428/problem/7816
luogu: https://www.luogu.com.cn/problem/P9755
*/
#define TASK "tree"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
using int128 = __int128;

#ifdef USACO_LOCAL_JUDGE
int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)               \
  do {                              \
    if (debug) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

void InitIO(){
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "2"
freopen(TASK TASKNO ".in", "r", stdin);
freopen(TASK TASKNO ".out", "w", stdout);
#endif
} ll rd() {
  ll x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  }
  return x * w;
}

vector<tuple<ll, ll, ll>> points;
vector<vector<ll>> g;
ll n;

vector<ll> lastDay;

/*
h=max(b+xc,1)
ci<0: b-c, b-2c, b-3c, ...,     1, 第 (b-1)/c 天是最后一天非 1， 第 (b-1)/c + 1 天变成 1
ci=0:   b,    b,    b, ...,     b
ci>0: b+c, b+2c, b+3c, ..., b+k*c

b+xc >= 1
b - 1 >= -cx
(b - 1) / (-c) >= x

*/

int128 mySqrt(int128 A) {
  // return sqrt(A);
  int128 l = sqrt(A);
  int128 r = l * 2;
  while (l < r) {
    int128 mid = (l + r) / 2;
    int128 mm = mid * mid;
    if (mm >= A) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  if (r * r > A) {
    r--;
  }
  return r;
}

// 判断 maxDay 天内，所有节点不考虑依赖，是否可以满足要求
bool CheckDownDay(int128 maxDay, int128 A, int128 B, int128 C, ll& ret) {
  int128 Y = maxDay;
  int128 lastVal = B - Y * C;
  MyAssert(lastVal > 0);
  int128 allHeight = ((B - C) + (B - Y * C)) * Y / 2;
  if (allHeight < A) {
    return false;
  } else if (allHeight == A) {
    ret = 1;
    return true;
  }
  if (B - Y * C >= A) {
    ret = maxDay;
    return true;
  }
  int128 AA = C;
  int128 BB = -(2 * B + C);
  int128 CC = (2 * B - Y * C) * (Y + 1) - 2 * A;
  int128 X = (-BB - mySqrt(BB * BB - 4 * AA * CC)) / (2 * AA);
  // k = -BB/(2*AA) = (2 * B + C)/(2*C) = B/C + 1/2
  MyAssert(X < maxDay);
  // if (X < maxDay) {
  //   X++;
  // }
  // if (X > maxDay) {
  //   X--;
  // }
  MyAssert((B + X * C + B + Y * C) * (Y - X + 1) / 2 >= A);
  // while ((B - X * C + B - Y * C) * (Y - X + 1) / 2 < A) {
  //   X--;
  // }
  ret = X;
  return true;
}
bool CheckLastDay(const int128 maxDay, const int128 A, const int128 B, int128 C, ll& ret) {
  if (C > 0) {
    const int128 Y = maxDay;
    const int128 allHeight = ((B + C) + (B + Y * C)) * Y / 2;
    if (allHeight < A) {
      return false;
    } else if (allHeight == A) {
      ret = 1;
      return true;
    }
    if (B + Y * C >= A) {  // 最后一天就够了
      ret = maxDay;
      return true;
    }
    // (B+X*C + B+Y*C) * (Y - X + 1) / 2 >= A
    // (2*B + Y*C + C*X) * (Y + 1 - X) >= 2*A
    // (2*B + Y*C) * (Y + 1) - (2*B + Y*C) * X + C * (Y + 1) * X - C * X^2 >= 2*A
    // (2*B + Y*C) * (Y + 1) + (C - 2 * B) * X - C * X^2 >= 2*A
    // C * X^2 + (2*B - C) * X + 2*A - (2*B + Y*C) * (Y + 1) <= 0
    // k = (C - 2 * B) / (2 * C) = 1 / 2 - B / C < 1
    int128 AA = C;
    int128 BB = 2 * B - C;
    int128 CC = 2 * A - (2 * B + Y * C) * (Y + 1);
    int128 X = (-BB + mySqrt(BB * BB - 4 * AA * CC)) / (2 * AA);  // 向下取整, X 更小
    // if (X < maxDay) {
    //   X++;
    // }
    MyAssert(X < maxDay);
    MyAssert((B + X * C + B + Y * C) * (Y - X + 1) / 2 >= A);
    // while ((B + X * C + B + Y * C) * (Y - X + 1) / 2 < A) {
    //   X--;
    // }
    ret = X;
    return true;
  } else if (C == 0) {
    ll minDay = (A + 1) / B;
    if (minDay > maxDay) {
      return false;
    }
    ret = maxDay - minDay + 1;
    return true;
  } else {
    C = -C;
    const ll oneDayBefor = (B - 1) / C;
    if (oneDayBefor >= maxDay) {  // 变成 1 之前
      return CheckDownDay(maxDay, A, B, C, ret);
    } else {  // 变成 1 之后
      const ll oneDayNum = maxDay - oneDayBefor;
      if (oneDayNum >= A) {  // 使用 1 就够了
        ret = maxDay - A + 1;
        return true;
      } else {  // 1 不够
        return CheckDownDay(maxDay - oneDayNum, A - oneDayNum, B, C, ret);
      }
    }
  }
}
ll Dfs(int u, int pre) {
  for (auto v : g[u]) {
    if (v == pre) continue;
    lastDay[u] = min(lastDay[u], Dfs(v, u) - 1);
  }
  return lastDay[u];
}
bool Check(ll maxDay) {
  // 第一步，计算每棵树最晚在哪天种植
  for (ll i = 0; i < n; i++) {
    auto [a, b, c] = points[i];
    if (!CheckLastDay(maxDay, a, b, c, lastDay[i])) {
      return false;
    }
  }
  // 第二步：递归计算出树，修正 lastDay，父亲的 lastDay 需要小于儿子的
  if (Dfs(0, -1) < 1) {
    return false;
  }
  // 第三步：排序
  sort(lastDay.begin(), lastDay.end());
  // 第四步：判断答案
  for (int i = 1; i <= n; i++) {
    if (lastDay[i - 1] < i) {
      return false;
    }
  }
  return true;
}

// ll SolverMinDay(ll a, ll b, ll c) {
//   if (c > 0) {
//     int128 AA = c;
//     int128 BB = 2 * b + c;
//     int128 CC = -2 * a;
//     int128 X = (sqrt(BB * BB - 4 * AA * CC) - BB) / (2 * AA);
//     if ((b + c + b + X * c) * X / 2 < a) {
//       X++;
//     }
//     return X;
//   } else if (c == 0) {
//     return (a + b - 1) / b;
//   } else {
//     c = -c;
//     int128 oneDay = (b - 1) / c;
//     int128 Y = (b - c + b + oneDay * c) * oneDay / 2;
//     if (Y < a) {
//       return oneDay + a - Y;  // 差的使用 1 补上
//     } else if (Y == a) {
//       return oneDay;  // 恰好够
//     } else {

//     }
//   }
// }
void Solver() {  //
  // scanf("%lld", &n);
  n = rd();
  points.reserve(n);
  lastDay.resize(n);
  // minDay.resize(n);
  g.resize(n);
  // myprintf("n=%lld\n", n);
  for (ll i = 0; i < n; i++) {
    ll a, b, c;
    a = rd();
    b = rd();
    c = rd();
    if (b + c <= 0) {  // 第一天就不满足
      b = 1;
      c = 0;
    }
    points.push_back({a, b, c});
    // minDay[i] = SolverMinDay(a, b, c);
  }
  for (ll i = 1; i < n; i++) {
    ll u, v;
    u = rd();
    v = rd();
    // scanf("%lld%lld", &u, &v);
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ll l = n, r = 10e9 + 1;
  while (l < r) {  //[l,r)
    ll mid = (l + r) / 2;
    // myprintf("l=%lld r=%lld mid=%lld\n", l, r, mid);
    if (Check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%lld\n", r);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
4
12 1 1
2 4 -1
10 3 0
7 10 -2
1 2
1 3
3 4

5




*/