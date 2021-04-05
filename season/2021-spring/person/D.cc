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
    int T, N, M;
    vector<vector<string>> maze;
    bool dfs(const int t, const int x, const int y, const int magic = 3, const int use = 0){
        if(x + 1 == N && y + 1 == M) return true;
        
        if(t + 1 == T) return false; //时间到了
        
        //printf("t=%d x=%d y=%d magic=%d use=%d\n", t,x,t,magic, use);
        
        if(have[t][x][y][magic][use]) return false;
        //printf("add\n");
        have[t][x][y][magic][use] = true;
        
        
        int dir[5][2] = {{1,0},{-1,0},{0,1},{0,-1},{0, 0}};
        for(int i = 0; i < 5; i++){
            int xx = x + dir[i][0];
            int yy = y + dir[i][1];
            if(xx < 0 || xx >= N || yy < 0 || yy >= M) continue; //越界
            
            if(i == 4 && use == 1){ // 待在原地
                if(dfs(t+1, xx, yy, magic, 1)){
                    return true;
                }
            }
            
            //printf("try t=%d xx=%d yy=%d\n", t+1,xx,yy);
            if(maze[t+1][xx][yy] == '.'){
                if(dfs(t+1,xx,yy,magic, 0)){
                    return true;
                }
            }else{
               if(magic&1){
                    if(dfs(t+1,xx,yy,magic&~1, 0)){
                        return true;
                    }
                }
                if(magic&2){
                    if(dfs(t+1,xx,yy,magic&~2, 1)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
 
public:
    bool escapeMaze(vector<vector<string>>& maze_) {
        maze.swap(maze_);
        
        T = maze.size(); //[[".#.","#.."],["...",".#."],[".##",".#."],["..#",".#."]]
        N = maze[0].size(); // [".#.","#.."]
        M = maze[0][0].size(); //".#."
        //printf("T=%d N=%d M=%d\n", T,N,M);
        
        memset(have, false, sizeof(have));
        
        return dfs(0, 0, 0);
    }
};


int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
