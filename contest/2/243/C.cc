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
  min_queue<pii> free_svr;       // 空闲服务器列表
  min_queue<pii> running_svr;    // 运行中的服务器列表
  min_queue<pii> pendding_task;  // 等待处理的任务列表
  vector<int> ans;
  int n;
  vector<int> servers;
  vector<int> tasks;

 public:
  void Init() {
    // 初始化
    for (int i = 0; i < servers.size(); i++) {
      free_svr.push({servers[i], i});
    }

    n = tasks.size();
    ans.resize(n, 0);
  }

  void CheckFinish(int now) {
    while (!running_svr.empty()) {
      auto p = running_svr.top();
      if (p.first > now) {  // 所有任务都在运行中
        return;
      }

      running_svr.pop();

      int svr_id = p.second;
      free_svr.push({servers[svr_id], svr_id});
    }
  }

  void AddPenddingTask(int index, int t) { pendding_task.push({index, t}); }

  void TryRunTask(int now) {
    CheckFinish(now);
    while (!pendding_task.empty() && !free_svr.empty()) {
      const auto [task_id, run_time] = pendding_task.top();
      pendding_task.pop();

      const auto [svr_weight, svr_id] = free_svr.top();
      free_svr.pop();

      running_svr.push({now + run_time, svr_id});
      ans[task_id] = svr_id;
    }
  }

  vector<int> assignTasks(vector<int>& servers_, vector<int>& tasks_) {
    servers.swap(servers_);
    tasks.swap(tasks_);

    Init();

    for (int i = 0; i < n; i++) {
      AddPenddingTask(i, tasks[i]);
      TryRunTask(i);
    }

    while (!pendding_task.empty()) {
      TryRunTask(running_svr.top().first);
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
