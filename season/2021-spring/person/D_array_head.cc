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

typedef long long ll;
class Solution {
    struct State{
        int t, x, y, magic; // 00 01 10 11
        int xx, yy;
        bool operator<(const State &t2)const {
            return this->x+this->y-this->t < t2.x + t2.y-t2.t;
        }
    };
    // hash: t * 100 + x(100) + y (100) + 4(10) + [100,100]
    
    unordered_set<ll> have;
    ll hash(int t, int x, int y, int magic, int xx = 0, int yy = 0){
        ll h = t;
        h = h * 100 + x;
        h = h * 100 + y;
        h = h * 10 + magic;
        h = h * 100 + xx;
        h = h * 100 + yy;
        return h;
    }
    
    queue<State> que;
    int T,N,M;
    
    void add(int t, int x, int y, int magic, int xx = 0, int yy = 0){
        ll h = hash(t, x, y, magic, xx, yy);
        if(have.count(h)) return;
        
       // printf("in %d: t=%d x=%d y=%d magic=%d xx=%d yy=%d\n",have.size(), t, x, y, magic, xx, yy);
        
        que.push(State{t, x, y, magic, xx, yy});
        have.insert(h);
    }
    
public:
    bool escapeMaze(vector<vector<string>>& maze) {
        
        T = maze.size(); //[[".#.","#.."],["...",".#."],[".##",".#."],["..#",".#."]]
        N = maze[0].size(); // [".#.","#.."]
        M = maze[0][0].size(); //".#."
        //printf("N=%d M=%d\n", N,M);
        int t = 0, x = 0, y= 0, magic = 3;
        
        add(t, x, y, magic);
        
        int dir[5][2] = {{0, 0}, {1,0},{-1,0},{0,1},{0,-1}};
        while(!que.empty()){
            const auto now = que.front(); que.pop();
            
            //printf("out t=%d x=%d y=%d magic=%d xx=%d yy=%d\n",now.t, now.x, now.y, now.magic, now.xx, now.yy);
                
            for(int i=0;i<5;i++){
                x = now.x + dir[i][0];
                y = now.y + dir[i][1];
                t = now.t + 1;
                magic= now.magic;
                
                if(x < 0 || x >= N || y < 0 || y >= M) continue;
                
                if(x == N - 1 && y == M - 1) return true;
                
                
                if(t + 1 == T){
                    continue;
                }
                
                if(maze[t][x][y] == '.'){
                    add(t, x, y, magic, now.xx, now.yy);
                    continue;
                }
                
                if(now.xx == x && now.yy == y){ // 下一步是永久消除，可以通过
                    add(t, x, y, magic, x, y);
                    continue;
                }
                
                if(magic&1){ //临时消除
                   add(t, x, y, magic & ~1, now.xx, now.yy);
                }
                if(magic & 2){ // 永久消除
                    add(t, x, y, magic & ~2, x, y);
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
