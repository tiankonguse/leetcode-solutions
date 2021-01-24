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
class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> ans(n, -1);
        
        vector<set<int>> balls(n+2);
        vector<set<int>> nextBalls(n+2);
        
        for(int i=1;i<=n;i++){
            balls[i].insert(i);
        }
        
        for(int i=1;i<=m;i++){
            nextBalls.clear();
            nextBalls.resize(n+2);
            
            for(int j=1;j<=n;j++){
                if(balls[j].size() == 0){
                    continue;
                }
                int dir = grid[i-1][j-1];
                if(dir == 1){ // 向右
                    if(j == n || grid[i-1][j] == -1){ // 撞墙
                        for(auto v: balls[j]){
                            ans[v - 1] = -1;
                        }
                    }else{
                        for(auto v: balls[j]){
                            nextBalls[j + 1].insert(v);
                            ans[v - 1] = j + 1;
                        }
                    }
                }else{
                    if(j == 1 || grid[i-1][j-2] == 1){
                        for(auto v: balls[j]){
                            ans[v - 1] = -1;
                        }
                    }else{
                        for(auto v: balls[j]){
                            nextBalls[j -1 ].insert(v);
                            ans[v - 1] = j - 1;
                        }
                    }
                }
            }
            balls.swap(nextBalls);
        }
        
        for(int i=0;i<n;i++){
            if(ans[i] > 0){
                ans[i]--;
            }
        }
        return ans;
    }
};

int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
