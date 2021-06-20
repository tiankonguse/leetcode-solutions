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
// int dir[8][2] = {{0,1},{1, 1},{1,0},{1,-1}, {0,-1}, {-1, -1}, {-1,0}, {-1, 1}};
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


bool dp[111][111];
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

class Solution {
    int k, n, m;

    int Step(int x, int y){
        int sum = 0;
        while(x){
            sum += x%10;
            x /= 10;
        }
        while(y){
            sum += y%10;
            y /= 10;
        }
        return sum;
    }
    int Dfs(int x, int y){
        if(x < 0 || y < 0 || x >= n || y >= m) return 0;
        if(dp[x][y]) return 0;
        dp[x][y] = true;
        if(Step(x, y) > k) return 0;

        int ans = 1;
        for(int i = 0; i < 4; i++){
            int X = x + dir[i][0];
            int Y = y + dir[i][1];
            ans += Dfs(X, Y);
        }
        return ans;
    }

public:
    int movingCount(int m_, int n_, int k_) {
        n = n_, m = m_, k = k_;
        memset(dp, false, sizeof(dp));
        return Dfs(0, 0);
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
