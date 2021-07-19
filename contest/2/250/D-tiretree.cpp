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

// int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
// int dir[8][2] = {{0,1},{1, 1},{1,0},{1,-1}, {0,-1}, {-1, -1}, {-1,0}, {-1,
// 1}}; lower_bound 大于等于 upper_bound 大于 vector/array:
// upper_bound(vec.begin(), vec.end(), v) map: m.upper_bound(v) reserve
// vector预先分配内存 reverse(v.begin(), v.end()) 反转 sum =
// accumulate(a.begin(), a.end(), 0); unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// __builtin_popcount 快速得到 1 的个数
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
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 2000100, max6 = 2000100;

const int kind = 2, N = max5;

class TireTree {
 public:
  int tire[N][kind], word[N];
  pair<int, int> pre[N];
  int num = 0;

  void Init() {
    memset(tire[0], 0, sizeof(tire[0]));
    memset(tire[1], 0, sizeof(tire[1]));
    pre[1] = {1, 0};
    num = 2;
  }
  void Insert(const int val) {
    int p = 1;
    for (int bit = 17; bit >= 0; bit--) {
      int v = (val >> bit) & 1;
      if (!tire[p][v]) {
        memset(tire[num], 0, sizeof(tire[num]));
        word[num] = 0;
        pre[num] = {p, v};
        tire[p][v] = num++;
      }
      p = tire[p][v];
    }
    word[p] = val;
  }
  void Erase(const int val) {
    int p = 1;

    // 先找到 p 的叶子节点
    for (int bit = 17; bit >= 0; bit--) {
      int v = (val >> bit) & 1;
      p = tire[p][v];
    }

    // 逆向的删除空叶子
    word[p] = 0;
    while (p != 1 && word[p] == 0 && tire[p][0] == 0 && tire[p][1] == 0) {
      auto father = pre[p];
      tire[father.first][father.second] = 0;
      if (p + 1 == num) {
        num--;
      }
      p = father.first;
    }
  }

  int QueryMaxXor(const int val) {
    int p = 1;
    for (int bit = 17; bit >= 0; bit--) {
      int v = (val >> bit) & 1;
      int xor_v = 1 - v;

      if (tire[p][xor_v]) {
        p = tire[p][xor_v];
      } else {
        p = tire[p][v];
      }
    }
    int ans = val ^ word[p];
    // printf("val=%d p=%d word[p]=%d ans=%d\n", val, p, word[p], ans);

    return ans;
  }
};

class Solution {
  int n;

  vector<vector<int>> tree;
  unordered_map<int, vector<pair<int, int>>> query_nodes;
  vector<int> ans;
  TireTree tire_tree;

  void Dfs(int node) {
    tire_tree.Insert(node);

    if (query_nodes.count(node)) {
      for (auto& p : query_nodes[node]) {
        ans[p.first] = tire_tree.QueryMaxXor(p.second);
      }
    }
    for (auto v : tree[node]) {
      Dfs(v);
    }

    tire_tree.Erase(node);
  }

 public:
  vector<int> maxGeneticDifference(vector<int>& parents,
                                   vector<vector<int>>& queries) {
    n = parents.size();
    tree.resize(n);
    ans.resize(queries.size(), 0);

    tire_tree.Init();

    int root_pos = -1;
    for (int i = 0; i < n; i++) {
      if (parents[i] == -1) {
        root_pos = i;
      } else {
        tree[parents[i]].push_back(i);
      }
    }

    for (int i = 0; i < queries.size(); i++) {
      int node = queries[i][0];
      int val = queries[i][1];

      query_nodes[node].push_back({i, val});
    }

    Dfs(root_pos);

    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
