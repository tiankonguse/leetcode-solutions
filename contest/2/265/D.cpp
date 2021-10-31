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

#define myprintf(format, args...) printf("line[%s]" format, __LINE__, ##args)
#define myprintf(format, args...)

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


#define myprintf(format, args...) printf("line[%s]" format, __LINE__, ##args)
#define myprintf(format, args...)

int dp[44][44][2][1000];

class Solution {
    string s1;
    string s2;
    
    bool isDigit (char c){
        return c >= '0' && c <= '9';
    }
    bool isLetter (char c){
        return c >= 'a' && c <= 'z';
    }
    
    int Dfs2(int p1, int ext1, int p2, int ext2){
        int ret = 0;

        int num = 0;
        for(int i = 0; i < 3 && isDigit(s2[p2 + i]); i++){
            num = num * 10 + s2[p2 + i] - '0';
            ret = Dfs(p1, ext1, p2 + i + 1, num);
            myprintf("15 i=%d p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", i, p1, ext1, p2, ext2, ret);
            if(ret) {
                return ret;
            }
        }

        myprintf("15 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
        return ret;
    }
    
    int Dfs1(int p1, int ext1, int p2, int ext2){
        int ret = 0;

        int num = 0;
        for(int i = 0; i < 3 && isDigit(s1[p1 + i]); i++){
            num = num * 10 + s1[p1 + i] - '0';
            ret = Dfs(p1 + i + 1, num, p2, ext2);
            myprintf("19 i=%d p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", i, p1, ext1, p2, ext2, ret);
            if(ret) {
                return ret;
            }
        }

        myprintf("20 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
        return ret;
    }
    
    int Dfs(int p1, int ext1, int p2, int ext2){
        if(ext1 > 0 && ext2 > 0) {
            int minExt = min(ext1, ext2);
            int ret = Dfs(p1, ext1 - minExt, p2, ext2 - minExt);
            myprintf("12 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
            return ret;
        }
        
        int flag = 0;
        int ext = ext1;
        if(ext2 > 0) {
            flag = 1;
            ext = ext2;
        }
        
        int& ret = dp[p1][p2][flag][ext];
        if(ret != -1) {
           myprintf("11 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
            return ret;
        }
        
        
        if(ext1 > 0 && ext2 == 0) { // ext2 = 0
            if(p2 == s2.size()) {
                ret = 0;
                //printf("13 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
                return ret;
            }
            
            if(isLetter(s2[p2])) {
                ret = Dfs(p1, ext1 - 1, p2 + 1, ext2);
                myprintf("14 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
                return ret;
            }
            return Dfs2(p1, ext1, p2, ext2);
        }else if(ext1 == 0 && ext2 > 0) {
            if(p1 == s1.size()) {
                ret = 0;
                myprintf("17 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
                return ret;
            }
            
            if(isLetter(s1[p1])) {
                ret = Dfs(p1 + 1, 0, p2, ext2 - 1);
                myprintf("18 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
                return ret;
            }
            return Dfs1(p1, ext1, p2, ext2);
        }else { // ext1 == 0 && ext2 == 0
            if(p1 == s1.size() && p2 == s2.size()) {
                ret = 1;
                myprintf("21 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
                return ret;
            }
            
            if(isLetter(s1[p1]) && isLetter(s2[p2])) {
                ret = 0;
                if(s1[p1] == s2[p2]) {
                    ret = Dfs(p1 + 1, 0, p2 + 1, 0);
                }
                myprintf("221 p1=%d ext1=%d p2=%d ext2=%d ret=%d\n", p1, ext1, p2, ext2, ret);
                return ret;
            }
            
            //至少有一个是数字
            if(isDigit(s1[p1])) {
                return Dfs1(p1, ext1, p2, ext2);
            } else {
                return Dfs2(p1, ext1, p2, ext2);
            }
        }
    }
    
    
public:
    bool possiblyEquals(string& s1_, string& s2_) {
        s1.swap(s1_);
        s2.swap(s2_);
        
        s1.push_back('a');
        s2.push_back('a');
        
        memset(dp, -1, sizeof(dp));
        
        return Dfs(0, 0, 0, 0);
    }
};

int main() {
    // bool ans = false;
    // string s1 = "ab";
    // string s2 = "a2";
    // TEST_SMP2(Solution, possiblyEquals, ans, s1, s2);

  return 0;
}
