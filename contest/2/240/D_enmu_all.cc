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
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  vector<unordered_set<int>> nextNodes;
  vector<int> zeroInDegNodes;
  vector<int> inDegs;
  vector<int> cache;
  string colors;
  int n;

  // 复杂度：O(m)
  void Init(vector<vector<int>>& edges) {
    nextNodes.clear();
    zeroInDegNodes.clear();
    inDegs.clear();
    cache.clear();

    n = colors.size();

    nextNodes.resize(n);

    inDegs.resize(n, 0);
    zeroInDegNodes.reserve(n);

    for (auto& v : edges) {
      int from = v[0], to = v[1];
      nextNodes[from].insert(to);
      inDegs[to]++;
    }

    for (int i = 0; i < n; i++) {
      if (inDegs[i] == 0) {
        zeroInDegNodes.push_back(i);
      }
    }
  }

  // 复杂度：O(m)
  bool CheckOk() {
    stack<int> sta;
    for (auto v : zeroInDegNodes) {
      sta.push(v);
    }

    int delNodeNum = 0;

    // 找到入度为0 的边，依次删除
    while (!sta.empty()) {
      int from = sta.top();
      sta.pop();
      delNodeNum++;

      for (auto to : nextNodes[from]) {
        inDegs[to]--;
        if (inDegs[to] == 0) {
          sta.push(to);
        }
      }
    }

    return delNodeNum == n;
  }

int Dfs(int from, char c) {
  if (cache[from] != -1) return cache[from];

  int ans = 0;
  for (auto to : nextNodes[from]) {
    ans = max(ans, Dfs(to, c));
  }
  if (colors[from] == c) {
    ans++;
  }
  return cache[from] = ans;
}

 public:
int largestPathValue(string& colors_, vector<vector<int>>& edges) {
  colors.swap(colors_);

  Init(edges);
  if (!CheckOk()) {
    return -1;  // 有环
  }

  int ans = 0;
  for (char c = 'a'; c <= 'z'; c++) {
    cache.clear();
    cache.resize(n, -1);
    for (int from : zeroInDegNodes) {
      ans = max(ans, Dfs(from, c));
    }
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
