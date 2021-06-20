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


int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

class Solution {
    vector<vector<char>> board;
    string word;
    int n, m, l;

    bool Dfs(int x, int y, int pos){
        if(pos == l) {
            return true;
        }

        if(x < 0 || y < 0 || x >= n || y >= m) return false;
        if(board[x][y] != word[pos]) return false;

        char c = board[x][y];
        board[x][y] = '0';
        for(int i = 0; i < 4; i++){
            int X = x + dir[i][0];
            int Y = y + dir[i][1];
            if(Dfs(X, Y, pos + 1)){
                return true;
            }
        }
        board[x][y] = c;
        return false;
    }

public:
    bool exist(vector<vector<char>>& board_, string& word_) {
        board.swap(board_);
        word.swap(word_);

        n = board.size();
        m = board[0].size();
        l = word.length();

        if(l == 0){
            return true;
        }

        if(l > n * m){
            return false;
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(board[i][j] != word[0]) continue;
                if(Dfs(i, j, 0)){
                    return true;
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
