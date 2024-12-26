#include "base.h"

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

// lower_bound 大于等于
// upper_bound 大于
// reserve
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

int maxPre[maxn];
int minPre[maxn];

int GetRight(int a) {
  //printf("GetRight a=%d\n", a);
  if (maxPre[a] == a) {
    return a;
  } else {
    return maxPre[a] = GetRight(maxPre[a]);
  }
}

int GetLeft(int a) {
  a = GetRight(a);
  return minPre[a];
}

void merge(int a, int b) {
  a = GetRight(a);
  b = GetRight(b);
    if(a == b){
        return;
    }
    
  minPre[a] = minPre[b] = min(minPre[a], minPre[b]);
  maxPre[a] = maxPre[b] = max(maxPre[a], maxPre[b]);
}
void init(int n) {
  for (int i = 0; i <= n; i++) {
    maxPre[i] = minPre[i] = i;
  }
}

int n;
vector<vector<int>> cars;

double GetTime(int a, int b) {
  //printf("GetTime a=%d b=%d\n", a, b);
  a = GetRight(a);
  b = GetRight(b);
    a--,b--;
  if (cars[a][1] <= cars[b][1]) {
    return -1;
  } else {
    return 1.0 * (cars[b][0] - cars[a][0]) / (cars[a][1] - cars[b][1]);
  }
}

double GetTime(int a) {
  //printf("GetTime a=%d n=%d\n", a, n);
  a = GetRight(a);
  if (a == n) {
    return -1;
  }
  return GetTime(a, a + 1);
}

pair<double, int> MyMin(pair<double, int> a, pair<double, int> b) {
  if (a.first < 0) {
    return b;
  } else if (b.first < 0) {
    return a;
  } else {
    return min(a, b);
  }
}

struct SegTree {
  LL sign[maxn << 2];  //
  pair<double, int> minVal[maxn << 2];

  LL str[maxn];

  void PushUp(int rt) {
    minVal[rt] = MyMin(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] = sign[rt];
      sign[rt << 1 | 1] = sign[rt];

      minVal[rt << 1] = minVal[rt];
      minVal[rt << 1 | 1] = minVal[rt];

      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      minVal[rt] = {GetTime(l), l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void update(int L, int R, pair<double, int> add, int l = 1, int r = maxNM,
              int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] = 1;
      minVal[rt] = add;
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, add, lson);
    if (R > m) update(L, R, add, rson);
    PushUp(rt);
  }
  pair<double, int> queryMin(int L, int R, int l = 1, int r = maxNM,
                             int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    pair<double, int> ret = {-1, 0};
    if (L <= m) {
      ret = MyMin(ret, queryMin(L, R, lson));
    }
    if (m < R) {
      ret = MyMin(ret, queryMin(L, R, rson));
    }
    return ret;
  }
};

class Solution {
 public:
  vector<double> getCollisionTimes(vector<vector<int>>& cars_) {
    cars.swap(cars_);
    n = cars.size();
    //printf("n=%d\n", n);
    maxNM = n;
    vector<double> ans(n, -1);

    init(n);

    SegTree segTree;
    segTree.Build();

    while (true) {
      // [a1, a2] [b1, b2] [c1, c2]
      // 此时 b 可以追上 c
        //printf("roud begin\n");
      auto p = segTree.queryMin(1, n);
      int posb = p.second;
      //printf("posb=%d t=%f\n", posb, p.first);
      if (p.first < 0) {
        break;
      }
      // 此时 pos 在下一时刻可以追上下一辆车
      posb = GetRight(posb);
      ans[posb - 1] = p.first;

      int posc = GetRight(posb + 1);
      double poscTime = GetTime(posc);
      //printf("posc=%d t=%f\n", posc, poscTime);

      //printf("merge posb=%d [%d, %d] to t=%f p=%d \n", posb, GetLeft(posb), GetRight(posb), poscTime, posc);
      //  [b1, b2] [c1, c2] => [b1, c2]
      segTree.update(GetLeft(posb), GetRight(posb), {poscTime, posc});
      merge(posb, posc);
        //printf("after merge: posb=%d [%d, %d]\n", posb, GetLeft(posb), GetRight(posb));
        //printf("after merge: posc=%d [%d, %d]\n", posc, GetLeft(posc), GetRight(posc));

      // 此时，posa 的答案会发生变化

      if (GetLeft(posb) == 1) {  // 没有上一个
        continue;
      }

      int posa = GetLeft(posb) - 1;
      double posaTime = GetTime(posa);
      //printf("posa=%d [%d,%d], t=%f\n", posa, GetLeft(posa), GetRight(posa), posaTime);
      // posa 到达下一位置需要的时间
      segTree.update(GetLeft(posa), GetRight(posa), {posaTime, posa});
        //printf("roud end\n");
    }

    return ans;
  }
};
int main() {
  vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
