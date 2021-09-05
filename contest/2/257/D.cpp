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
// __builtin_popcount 快速得到 1 的个数
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



/*
筛素数
*/

const int N = 100010;
const int M = 300;
bool is[N];
int prm[M];
int K = 0;
int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N && k < M; i += 2)
    if (is[i]) prm[k++] = i;
  return k;
}



int pre[N], rank_score[N];
void init(int n) {
  for (int i = 0; i < n; i++) {
    pre[i] = i, rank_score[i] = 0;
  }
}
int find_pre(int node) {
  if (pre[node] != node) {
    pre[node] = find_pre(pre[node]);
  }
  return pre[node];
}

void merge_pre(int from, int to) {
  from = find_pre(from);
  to = find_pre(to);
  if (from != to) {
    if (rank_score[from] > rank_score[to]) {
      pre[to] = from;
    } else {
      pre[from] = to;
      if (rank_score[from] == rank_score[to]) {
        ++rank_score[to];
      }
    }
  }
}


int fir[N], toV[N],  next_tree[N], cnt;
void addedge(int u, int v) {
  toV[cnt] = v;
  next_tree[cnt] = fir[u];
  fir[u] = cnt++;
}
void init_tree(int nv) {
  memset(fir, -1, sizeof(fir));
  cnt = 0;
}

int ans[N], tmp[N];

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        
        if(K == 0){
            K = getprm();
        }
        
        
        init(n);
        init_tree(n);
        for(int i = 0; i < K; i++){
            int pre_val = -1;
            for(int j=0;j<n;j++){
                if(nums[j] % prm[i] == 0){
                    if(pre_val == -1) {
                        pre_val = j;
                    }else{
                        merge_pre(pre_val, j);
                    }
                }
            }
        }
        
        for(int i = n - 1; i >= 0; i--){
            int root = find_pre(i);
            addedge(root, i);
        }
        
        for(int i=0;i<n;i++){
            ans[i] = nums[i];
        }
        
        for(int i=0;i<n;i++) {
            if(fir[i] == -1) continue;
            int tmp_num = 0;
            for(int pos = fir[i]; pos != -1; pos = next_tree[pos]) {
                int v = toV[pos];
                tmp[tmp_num++] = v;
            }
            sort(tmp, tmp + tmp_num, [](int a, int b){
                return ans[a] < ans[b];
            });
            for(int pos = fir[i], i = 0; pos != -1; pos = next_tree[pos],i++) {
                int v = toV[pos];
                ans[v] = nums[tmp[i]];
            }
            
        }
        
        for(int i = 1; i < n; i++){
            if(ans[i] < ans[i-1]) return false;
        }
        return true;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
