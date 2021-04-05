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
  struct State {
    int t, x, y, magic;
    bool operator<(const State &t2)const {
        return this->x+this->y-this->t < t2.x + t2.y-t2.t;
    }
  };
  // hash: t * 100 + x(100) + y (100) + 4(10) + [100,100]

  unordered_set<ll> have;
  ll hash(int t, int x, int y, int magic) {
    ll h = 0;
    h = h * 100 + t;
    h = h * 100 + x;
    h = h * 100 + y;
    h = h * 10 + magic;
    return h;
  }

  priority_queue<State> que;

  void add(int t, int x, int y, int magic) {
    ll h = hash(t, x, y, magic);
    if (have.count(h)) return;

    //printf("in %d: t=%d x=%d y=%d magic=%d\n",have.size(), t, x,y);

    que.push(State{t, x, y, magic});
    have.insert(h);
  }

  int T, X, Y;
  bool Try(int xx, int yy, vector<vector<string>>& maze) {
    have.clear();
    while (!que.empty()) {
      que.pop();
    }

    add(0, 0, 0, 1);

    int dir[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!que.empty()) {
      const auto now = que.top();
      que.pop();

       //printf("out t=%d x=%d y=%d magic=%d\n",now.t, now.x, now.y, now.magic);

      for (int i = 0; i < 5; i++) {
        int x = now.x + dir[i][0];
        int y = now.y + dir[i][1];
        int t = now.t + 1;
        int magic = now.magic;

        if (x < 0 || x >= X || y < 0 || y >= Y) continue;

        if (x == X - 1 && y == Y - 1) return true;

        if (t + 1 == T) {
          continue;
        }

        if (maze[t][x][y] == '.') {
          add(t, x, y, magic);
          continue;
        }

        if (xx == x && yy == y) {  // 下一步是永久消除，可以通过
          add(t, x, y, magic);
          continue;
        }

        if (magic & 1) {  //临时消除
          add(t, x, y, 0);
        }
      }
    }
      return false;
  }

 public:
  bool escapeMaze(vector<vector<string>>& maze) {
    T = maze.size();  //[[".#.","#.."],["...",".#."],[".##",".#."],["..#",".#."]]
    X = maze[0].size();     // [".#.","#.."]
    Y = maze[0][0].size();  //".#."
    // printf("N=%d M=%d\n", N,M);

    for (int i = 0; i < X; i++) {
      for (int j = 0; j < Y; j++) {
        if (Try(i, j, maze)) {
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
