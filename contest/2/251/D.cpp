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


const uint64_t INF = 0x3f3f3f3f3f3f3f3fll;

class Solution {
    struct Path{
        std::string name;
        map<string, Path> sub_path;
        bool leef = false;
        bool del_flag = false;
        uint64_t hash = 0;
    };
    Path root;
    unordered_map<uint64_t, Path*> first_hash; //之后的一旦存在，就要删除
    
    void AddPath(const vector<string>& path){
        Path* pre = &root;
        Path* now = NULL;
        for(auto& s: path){
            if(!pre->sub_path.count(s)) {
                pre->sub_path[s].name = s;
            }
            pre = &pre->sub_path[s];
        }
        pre->leef = true;
    }
    uint64_t HashName(const std::string& name){
        uint64_t h = 0x3f3f3f3f;
        for(auto c: name) {
            int v = c;
            h = h * 1000000007 + v;
        }
        return h;
    }
    
    uint64_t DfsHash(Path* now, int lev){
        uint64_t h = 0x3f3f3f3f;
        for(auto& p: now->sub_path){
            h = h * 1000000007 + DfsHash(&p.second, lev + 1);
        }
        now->hash = h;
        
        if(now->sub_path.size() > 0){
            //printf("/name=%s hash=%llu lev=%d del=%d\n", now->name.c_str(), h, lev);
            if(first_hash.count(h)) {
                first_hash[h]->del_flag = true;
                now->del_flag = true;
            }else{
                first_hash[h] = now;
            }
        }
        return HashName(now->name) * h;
    }
    
    vector<vector<string>> ans;
    
    bool DfsAns(Path* now, vector<string>& pre){
        if(now->del_flag) return true;
        
        pre.push_back(now->name);
        
        bool is_all_del = true;
        for(auto& p: now->sub_path){
            if(DfsAns(&p.second, pre)) {
                is_all_del = false;
            }
        }
        
        if(now->leef || is_all_del){
            ans.push_back(pre);
        }
        
        pre.pop_back();
        return false;
    }
    
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        for(auto& p: paths) {
            AddPath(p);
        }
        
        DfsHash(&root, 0);
        
        vector<string> tmp;
        for(auto& p: root.sub_path){
            DfsAns(&p.second, tmp);
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
