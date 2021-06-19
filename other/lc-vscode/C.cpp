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


int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

class Solution {
    int n, m;
    vector<string> grid;
    
    int DfsClear(int x, int y, char c){
        if(x < 0 || y < 0 || x >=n || y >=m) return 0;
        if(grid[x][y] == '6') return 0;
        if(c == '0'){
            c = grid[x][y];
        }else{
            if(grid[x][y] != c) return 0;
        }
        
        
        grid[x][y] = '6'; // clear
        int ans = 1;
        for(int i=0;i<4;i++){
            int X = x + dir[i][0];
            int Y = y + dir[i][1];
            ans += DfsClear(X, Y, c);
        }
        return ans;
    }
    
public:
    int largestArea(vector<string>& grid_) {
        grid.swap(grid_);
        
        n = grid.size();
        m = grid[0].size();
        
        for(int i=0;i<n;i++){
            DfsClear(i, 0, grid[i][0]);
            DfsClear(i, m-1, grid[i][m-1]);
        }
        for(int i=0;i<m;i++){
            DfsClear(0, i, grid[0][i]);
            DfsClear(n-1, i, grid[n-1][i]);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == '0'){
                    DfsClear(i, j, grid[i][j]);
                }
            }
        }
        
        for(int i=0;i<n;i++){
            printf("%d:%s\n", i, grid[i].c_str());
        }
        
        int ans = 0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans = max(ans, DfsClear(i, j, grid[i][j]));
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
