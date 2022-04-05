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

// 基本思路，BFS，每个节点至多入队一次，for 循环内每个节点只扫描一次
// 复杂度：O(n)
class Solution {
public:
    int minJump(vector<int>& jump) {
        int n = jump.size();

        vector<int> vis(n, 0);
        queue<pair<int, int>> que;
        que.push({0, 0});
        vis[0] = 1;

        int max_left = 1;

        while(!que.empty()){
            auto [v, step] = que.front(); que.pop();
            int next_pos = v + jump[v];
            if(next_pos >= n){
                return step + 1;
            }

            if(vis[next_pos] == 0){ // 向后跳
                que.push({next_pos, step + 1});
                vis[next_pos] = 1;
            }

            // 向前跳
            for(;max_left <= v; max_left++){
                if(vis[max_left]) continue;
                que.push({max_left, step + 1});
                vis[max_left] = 1;
            }
        }

        return 0;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
