#include "base.h"

#define myprintfex(format, args...) printf("line[%d]" format, __LINE__, ##args)
// #define myprintfex(format, args...)

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

/*
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int dir[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

lower_bound 大于等于
upper_bound 大于

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);
std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

vector预先分配内存 reserve
反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0);
unordered_map / unordered_set

__builtin_popcount 一的个数

size_t found=str.find(string/char/char*);
std::string::npos

排序，小于是升序：[](auto&a, auto&b){ return a < b; })
优先队列 priority_queue<Node>：top/pop/push/empty
struct Node {
  Node(int t = 0) : t(t) {}
  int t;
  // 小于是最大堆，大于是最小堆
  bool operator<(const Node& that) const { return this->t < that.t; }
};

mutex mtx;       // 互斥量，锁，定义一个即可
condition_variable cv; // 条件变量
cv.notify_one(); // 事件通知
unique_lock<mutex> lck(mtx);
cv.wait(lck); //等待事件

atomic_int tick; // 原子计数
this_thread::yield();  // 线程 sleep

#include <semaphore.h> // 需要手动包含信号量头文件
sem_t sem_done;
sem_init(&bar_done, 0 , 1);
sem_wait(&bar_done);
sem_post(&foo_done);

*/

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
    struct Node{
        int inLoop; // 是否在环上
        int pre; // 在环上时，环的唯一标示
        int rank; // 选自己时，答案是多少
        int flag; // 是否计算过
        int extNum; //  
        int realPre; //
        Node(){
            inLoop = 0;
            pre = -1;
            rank = 0;
            flag = 0;
            extNum = 0;
            realPre = -1;
        }
    };
    vector<int> nums;
    vector<Node> nodes;
    
    vector<int> stack;
    vector<int> hash;
    vector<int> ans;
    
    int maxLoop;
    
    
    void Dfs(int now){
        Node& node = nodes[now];
        if(node.flag == 1) {
            return;
        }
        // printf("in now = %d\n", now);
        
        node.flag = 1;
        stack.push_back(now);
        hash[now] = 1;
        
        int pre = nums[now];
        if(hash[pre] == 1) { // 形成一个环
            int loopSize = 0;
            int loopMin = now;
            
            for(int i = stack.size() - 1; i >= 0; i--) {
                int v = stack[i];
                
                loopSize++;
                loopMin = min(loopMin, v);
                if(v == pre) {
                    break;
                }
            }
            
            maxLoop = max(maxLoop, loopSize);
            
            // printf("loop, loopSize=%d loopMin=%d pre=%d \n", loopSize, loopMin, pre);
            for(int i = stack.size() - 1; i >= 0; i--) {
                int v = stack[i];
                
                nodes[v].inLoop = 1;
                nodes[v].pre = loopMin;
                nodes[v].rank = loopSize;
                nodes[v].realPre = v; 
                nodes[v].extNum = loopSize; 
                
                if(v == pre) {
                    break;
                }
            }
        }
        
        
        Dfs(pre);

        if(node.inLoop == 0) { 
            node.inLoop = 0;
            node.pre = nodes[pre].pre;
            node.rank = nodes[pre].rank + 1;
            
            int realPre = node.realPre = nodes[pre].realPre;
            nodes[realPre].extNum = max(nodes[realPre].extNum, node.rank);
        }
        
        if(nodes[node.pre].rank == 2) {
            int realPre = node.realPre;
            int nextPre = nums[realPre];
            
            ans[node.pre] = max(ans[node.pre], nodes[realPre].extNum + nodes[nextPre].extNum - nodes[realPre].rank);
            // printf("may ans: now = %d ans=%d\n", now, ans[node.pre]);
        }
        
        
        stack.pop_back();
        hash[now] = 0;
        
        return;
    }
    
public:
    int maximumInvitations(vector<int>& nums_) {
        nums.swap(nums_);
        
        int n = nums.size();
        nodes.resize(n);
        hash.resize(n, 0);
        ans.resize(n, 0);
        stack.reserve(n);
        maxLoop = 0;
        
        for(int i = 0; i < n; i++) {
            Dfs(i);
        }
        
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += ans[i];
        }
        
        return max(sum, maxLoop);
    }
};

int main() {
    int ans = 2;
    vector<int> nums = {1,0,0,2,1,4,7,8,9,6,7,10,8};
    TEST_SMP1(Solution, maximumInvitations, ans, nums);


  return 0;
}
