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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

struct Point {
  int a, b, h;  // 高为 c
  int num;
  int index;
  int pre_val;
  int in_egree;
  vector<int> edges;
  Point(int a, int b, int h, int num, int index)
      : a(a), b(b), h(h), num(num), index(index) {
    pre_val = 0, in_egree = 0;
  }
};

bool isEdge(Point& p1, Point& p2) {
  return p1.a <= p2.a && p1.b <= p2.b && p1.h <= p2.h;
}

class Solution {
  map<int, int> m;                // 100 个
  vector<Point> vec;              // 600 个
  set<int> zero_in_degree_nodes;  //入度为 0 的节点列表
  int n;

  int encode(vector<int>& v) { return v[0] * 1000000 + v[1] * 1000 + v[2]; }
  vector<int> decode(int h) {
    vector<int> v;
    v.push_back(h % 1000);
    v.push_back((h / 1000) % 100);
    v.push_back(h / 1000000);
    return v;
  }
  void MergeCuboids(vector<vector<int>>& cuboids) {
    for (auto& v : cuboids) {
      sort(v.begin(), v.end());
      int h = v[0] * 1000000 + v[1] * 1000 + v[2];
      m[h]++;
    }
  }

  void ConstructNode() {
    vec.reserve(m.size() * 6);
    int dir[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                     {1, 2, 0}, {2, 1, 0}, {2, 0, 1}};

    int index = 0;  // 给所有顶点分配编号
    for (auto [h, num] : m) {
      vector<int> v = decode(h);
      for (int i = 0; i < 6; i++) {
        int a = v[dir[i][0]];
        int b = v[dir[i][1]];
        int h = v[dir[i][2]];
        vec.push_back(Point(a, b, h, num, index));
        zero_in_degree_nodes.insert(index);
        index++;
      }
    }
    n = index;
  }

  void ConstructEdge() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i / 6 == j / 6) continue;  //同一个方块
        if (isEdge(vec[i], vec[j])) {  // j 可以放在 i 下面
          vec[j].edges.push_back(i);
          vec[i].in_egree++;
          zero_in_degree_nodes.erase(i);
        }
      }
    }
  }

 public:
  int maxHeight(vector<vector<int>>& cuboids) {
    // 第一步，合并相同的节点
    MergeCuboids(cuboids);

    // 第二部，构造节点
    ConstructNode();

    // 第三步，构图，同一个方块之间不能有边，不同方块之间可以证明没有环
    ConstructEdge();

    //第四步，求求最小生成树

    int ans = 0;
    while (!zero_in_degree_nodes.empty()) {
      int now = *(zero_in_degree_nodes.begin());
      zero_in_degree_nodes.erase(zero_in_degree_nodes.begin());

      Point& p1 = vec[now];
      int now_val = p1.pre_val + p1.h * p1.num;
      ans = max(ans, now_val);

      for (auto v : p1.edges) {
        Point& p2 = vec[v];
        p2.in_egree--;
        p2.pre_val = max(p2.pre_val, now_val);

        if (p2.in_egree == 0) {
          zero_in_degree_nodes.insert(v);
        }
      }
    }
    return ans;
  }
};

int main() {
  TEST_SMP1(
      Solution, maxHeight, 190,
      std::vector<vector<int>>({{50, 45, 20}, {95, 37, 53}, {45, 23, 12}}));
  TEST_SMP1(Solution, maxHeight, 76,
            std::vector<vector<int>>({{38, 25, 45}, {76, 35, 3}}));
  TEST_SMP1(Solution, maxHeight, 102,
            std::vector<vector<int>>({{7, 11, 17},
                                      {7, 17, 11},
                                      {11, 7, 17},
                                      {11, 17, 7},
                                      {17, 7, 11},
                                      {17, 11, 7}}));

  return 0;
}
