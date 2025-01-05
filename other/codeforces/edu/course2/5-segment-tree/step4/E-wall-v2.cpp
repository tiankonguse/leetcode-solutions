/*
ID: tiankonguse
TASK: E. Wall  E·沃尔
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/E
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤4 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
DESC: AC
*/
#define TASK "E-wall"
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod_10_9_7 = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

int maxNM;

typedef long long ll;

enum { UP = 1, DOWN = 2 };
struct Node {
  vector<pair<int, ll>> ops;
};
void Merge(const vector<pair<int, ll>>& os, vector<pair<int, ll>>& ops) {
  int n = ops.size();
  if (n == 0) {
    ops = os;
    return;
  }

  if (int(os.size()) == 1) {
    auto& o = os.front();
    if (n == 1) {
      auto& a = ops.front();
      if (a.first == o.first) {
        if (o.first == UP) {
          a.second = max(a.second, o.second);
        } else {
          a.second = min(a.second, o.second);
        }
      } else {
        if (o.first == UP) {  // 先 down 再 up，消除大于 up 的峰值
          if (a.second < o.second) {
            a.second = o.second;  // down 的比较小，up 的比较大，down 的值没意义，与 up 对齐
          }
          ops.push_back(o);
          swap(ops.back(), ops.front());  // 谁先谁后等价，交换位置，保证先 UP 再 DOWN
        } else {                          // 先 up 再 down，消除小于 down 的低谷
          if (a.second > o.second) {
            a.second = o.second;
          }
          ops.push_back(o);
        }
      }
    } else {
      auto& a = ops.front();       // UP
      auto& b = ops.back();        // DOWN
      if (a.second == b.second) {  // up 与 down 相等，值固定
        if (o.first == UP) {
          if (o.second > a.second) {
            a.second = b.second = o.second;  // 值已经固定，全部升高
          } else {
            // 都大于，忽略
          }
        } else {
          if (o.second < a.second) {
            a.second = b.second = o.second;  // 值已经固定，全部降低
          } else {
            // 都小于，忽略
          }
        }
      } else {
        if (o.first == DOWN) {
          if (o.second >= b.second) {
            // do nothing
          } else if (o.second > a.second && o.second < b.second) {
            b.second = o.second;
          } else {                           // o.second <= b.second
            a.second = b.second = o.second;  // 值已经固定
          }
        } else {
          if (o.second <= a.second) {
            // do nothing
          } else if (o.second > a.second && o.second < b.second) {
            a.second = o.second;
          } else {                           // o.second >= b.second
            a.second = b.second = o.second;  // 值已经固定
          }
        }
      }
    }
  } else {
    auto& o1 = os.front();  // UP
    auto& o2 = os.back();   // DOWN
    if (n == 1) {
      if (o1.second == o2.second) {  // 固定值
        ops = os;
      } else {  // a->o1(UP)->o2(DOWN)  UP < DOWN
        auto& a = ops.front();
        if (a.first == UP) {
          if (a.second <= o1.second) {
            ops = os;
          } else if (a.second > o1.second && a.second < o2.second) {
            ops.push_back(o2);
          } else {
            a.second = o2.second;
            ops.push_back(o2);
          }
        } else {
          if (a.second >= o2.second) {
            ops = os;
          } else if (a.second < o2.second && a.second > o1.second) {
            ops.push_back(o1);
            swap(ops.front(), ops.back());
          } else {
            a.second = o1.second;
            ops.push_back(o1);
            swap(ops.front(), ops.back());
          }
        }
      }
    } else {
      auto& a = ops.front();  // UP
      auto& b = ops.back();   // DOWN

      // a(up)->b(down)->o1(up)->o2(down)
      if (o1.second == o2.second) {
        ops = os;
      } else if (a.second == b.second) {
        if (o1.second > a.second) {
          a.second = b.second = o1.second;
        }
        if (o2.second < a.second) {
          a.second = b.second = o2.second;
        }
      } else {
        if (o1.second >= b.second) {
          a.second = b.second = o1.second;
        } else if (o2.second <= a.second) {
          a.second = b.second = o2.second;
        } else {
          a.second = max(a.second, o1.second);
          b.second = min(b.second, o2.second);
        }
      }
    }
  }
}
struct SegTree {
  vector<ll> flag;       // 延迟标记
  vector<Node> signVal;  // 延迟标记 {max, min}

  void Init(int n) {
    maxNM = n + 1;
    flag.resize(maxNM << 2, 0);  // 全部打上延迟标记，都是 W 颜色
    signVal.resize(maxNM << 2);
  }

  void UpdateNode(int rt, int l, int r, const vector<pair<int, ll>>& o) {
    flag[rt] = 1;
    Merge(o, signVal[rt].ops);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
  }
  void PushDown(int rt, int l, int r) {
    if (flag[rt] == 0) return;

    int m = (l + r) >> 1;
    UpdateNode(rt << 1, l, m, signVal[rt].ops);
    UpdateNode(rt << 1 | 1, m + 1, r, signVal[rt].ops);
    flag[rt] = 0;
    signVal[rt].ops.clear();
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      flag[rt] = 1;
      signVal[rt].ops.push_back({UP, 0});
      signVal[rt].ops.push_back({DOWN, 0});
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, const vector<pair<int, ll>>& o, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, o);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, o, lson);
    if (R > m) Update(L, R, o, rson);
    PushUp(rt, l, r);
  }
  vector<ll> ans;
  void QuerySum(int n, int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      if (l <= n) {
        ans[l] = signVal[rt].ops.front().second;
      }
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    QuerySum(n, lson);
    QuerySum(n, rson);
  }
};

int n, m;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
}

SegTree segTree;
void Solver() {  //
  segTree.Init(n);
  segTree.Build();
  vector<pair<int, ll>> os(1);
  while (m--) {
    int op;
    int l, r;
    ll d;
    scanf("%d%d%d%lld", &op, &l, &r, &d);
    os[0] = {op, d};
    segTree.Update(l + 1, r + 1, os);
  }
  segTree.ans.reserve(n + 1);
  segTree.QuerySum(n);
  for (int i = 1; i <= n; i++) {
    printf("%lld\n", segTree.ans[i]);
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
  // ll a = mod_10_9_7;
  // printf("a=%lld\n", a * a);
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/