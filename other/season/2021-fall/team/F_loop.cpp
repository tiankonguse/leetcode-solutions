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
// __builtin_popcount 一的个数
// size_t found=str.find(char/char*/string); std::string::npos
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

// mutex mtx;       // 互斥量，锁，定义一个即可
// condition_variable cv; // 条件变量
// cv.notify_one(); // 事件通知
// unique_lock<mutex> lck(mtx); 
// cv.wait(lck); //等待事件

// atomic_int tick; // 原子计数
// this_thread::yield();  // 线程 sleep

// #include <semaphore.h> // 需要手动包含信号量头文件
// sem_t sem_done;
// sem_init(&bar_done, 0 , 1);
// sem_wait(&bar_done);
// sem_post(&foo_done);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;



typedef long long LL;

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 50010;

int maxNM;
vector<long long> str;

struct SegTree {
  LL bitVal[maxn << 2];
  LL maxMal[maxn << 2];
  

  void PushUp(int rt) {
    bitVal[rt] = bitVal[rt << 1] | bitVal[rt << 1 | 1];
    maxMal[rt] = max(maxMal[rt << 1], maxMal[rt << 1 | 1]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      bitVal[rt] = maxMal[rt] = str[l - 1];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  LL queryBit(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return bitVal[rt];
    }
      
    int m = (l + r) >> 1;
    LL ret = 0;
    if (L <= m) {
      ret |= queryBit(L, R, lson);
    }
    if (m < R) {
      ret |= queryBit(L, R, rson);
    }
    return ret;
  }
  LL queryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxMal[rt];
    }
      
    int m = (l + r) >> 1;
    LL ret = 0;
    if (L <= m) {
      ret = max(ret, queryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, queryMax(L, R, rson));
    }
    return ret;
  }
};

SegTree lineSegTree;

class Solution {
    int n;
    
    int SearchLeftMax(LL score, int base){
        int l = 1, r = base;
        while(l < r) { //[l, r]
            int mid = (l + r)/2;
            //printf("mid=%d base=%d max=%llu\n", mid, base, lineSegTree.queryMax(mid, base));
            if(lineSegTree.queryMax(mid, base) <= score) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        // while(lineSegTree.queryMax(l, base) > score) {
        //     l++;
        // }
        return l;
    }
        
    int SearchRightMax(LL score, int base){
        int l = base, r = n;
        while(l < r) { //[l, r]
            int mid = (l + r)/2;
            if(lineSegTree.queryMax(base, mid) <= score) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        // while(lineSegTree.queryMax(base, r) > score) {
        //     r--;
        // }
        return r;
    }
    bool CheckPos(LL score, int pos){
        int l = pos, r = pos;
        int num = 1;
        
        int flag = true;
        while(flag && num < n) {
            flag = false;
            //[5,4,6,2,7]
            // pos=4 score=6 l=4 r=4 num=1
            //printf("pos=%d score=%llu l=%d r=%d num=%d\n", pos, score, l, r , num);
            if(l == 1 && str[n-1] <= score) { // 边界
                score |= str[n-1];
                num++;
                l = n;
                flag = true;
                continue;
            }
            
            
            if(l > 1 && str[l-2] <= score) {
                // int pos = SearchLeftMax(score, l);
                //printf("left max pos = %d\n", pos);
                // score |= lineSegTree.queryBit(pos, l);
                // num += l - pos;
                // l = pos;
                score |= str[l-2];
                num++;
                l--;
                flag = true;
                continue;
            }
            
            if(r == n && str[0] <= score) {
                num++;
                score |= str[0];
                r = 1;
                flag = true;
                continue;
            }
            
            
            if(r < n && str[r] <= score) {
                // int pos = SearchRightMax(score, r);
                // score |=  lineSegTree.queryBit(r, pos);
                // num += pos - r;
                // r = pos;
                score |= str[r];
                num++;
                r++;
                flag = true;
                continue;
            }
            
        }
        return num >= n;
    }
    
    bool CheckScore(LL score){
        for(int i = 1; i <= n; i++) {
            if(str[i-1] > score) continue;
            if(CheckPos(score | str[i-1], i)){
                return true;
            }
        }
        return false;
    }
    
public:
    long long ringGame(vector<long long>& challenge_) {
        // 二分积分， 枚举位置，线段树判断，复杂度：O( log(n) * n * log(n))
        str.swap(challenge_);
        
        n = maxNM = str.size();
        
        lineSegTree.Build();
        
        LL ans = 0;
        for(auto v: str) {
            ans = max(ans, v);
        }
        
        LL preAns = 0;
        
        LL one = 1;
        for(int i = 62; i >= 0; i--) {
            LL b = one << i;
            if(CheckScore((preAns | b) - 1)) {
                ans = min(ans, (preAns | b) - 1);
            } else{
                preAns |= b;
            }
        }
        if(CheckScore(preAns)) {
            ans = min(ans, preAns);
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
