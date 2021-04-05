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
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

 bool have[102][52][52][4][2]; // [T][N][M][magic][stay]
class Solution {
    struct State{
        int t, x, y, magic, use;
    };
    queue<State> que;
    
    void add(int t, int x, int y, int magic, int use = 0){
        if(have[t][x][y][magic][use]) return;
        que.push(State{t, x, y, magic, use});
        have[t][x][y][magic][use] = true;
    }
    
public:
    bool escapeMaze(vector<vector<string>>& maze) {
        memset(have, false, sizeof(have));
        int T = maze.size(); //[[".#.","#.."],["...",".#."],[".##",".#."],["..#",".#."]]
        int N = maze[0].size(); // [".#.","#.."]
        int M = maze[0][0].size(); //".#."
        //printf("N=%d M=%d\n", N,M);
        
        add(0, 0, 0, 3);
        
        int dir[5][2] = {{0, 0}, {1,0},{-1,0},{0,1},{0,-1}};
        while(!que.empty()){
            const auto now = que.front(); que.pop();
            
            //printf("out t=%d x=%d y=%d magic=%d xx=%d yy=%d\n",now.t, now.x, now.y, now.magic, now.xx, now.yy);
                
            for(int i=0;i<5;i++){
                int x = now.x + dir[i][0];
                int y = now.y + dir[i][1];
                int t = now.t + 1;
                int magic= now.magic;
                int use = now.use;
                
                if(x < 0 || x >= N || y < 0 || y >= M) continue;
                if(x == N - 1 && y == M - 1) return true;
                if(t + 1 == T) continue;
                
                if(i == 0 && use == 1){ // 待在原地
                    add(t, x, y, magic, use);
                    continue;
                }

                if(maze[t][x][y] == '.'){ // 走出去
                    add(t, x, y, magic, 0);
                    continue;
                }
                
                if(magic&1){ //临时消除
                   add(t, x, y, magic & ~1, 0);
                }
                if(magic & 2){ // 永久消除, 标记一下
                    add(t, x, y, magic & ~2, 1);
                }
            }
            
        }
        return false;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
