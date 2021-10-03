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


class Solution {
    vector<int> dp[26];
    vector<int> nextLetter;
    string ans;
    
public:
    string smallestSubsequence(string& s, int k, char letter, int repetition) {
        ans.reserve(k);
        
        int n = s.length();
        nextLetter.resize(n + 1, 0);
        for(int i = n - 1; i >= 0; i--) {
            nextLetter[i] = nextLetter[i + 1];
            if(s[i] == letter) {
                nextLetter[i]++;
            }
        }
        
        for(int i = 0; i < 26; i++) dp[i].resize(n + 1, -1);
        for(int i = n - 1; i >= 0; i--) {
            for(int j = 0; j < 26; j++) dp[j][i] = dp[j][i+1];
            dp[s[i] - 'a'][i] = i;
        }
        
        int preNum = 0;
        auto Check = [&](int pos){
            //i=1 c=e nextPos=2 ans=ee preNum=2 check=0 
            // printf("ans.length() + (n - pos)=%d k=%d\n", ans.length() + (n - pos), k);
            // printf("preNum + nextLetter[pos]=%d, repetition=%d\n", preNum + nextLetter[pos], repetition);
            // printf("k - ans.length()=%d, repetition - preNum=%d\n", k - ans.length(), repetition - preNum);
            if(ans.length() + (n - pos) < k) return false; // 长度不够了
            if(preNum + nextLetter[pos] < repetition) return false; // letter 不够了
            if(k - int(ans.length()) < repetition - preNum) return false; // 
            return true;
        };
        
        int pos = 0;
        for(int i = 0; i < k; i++) {
            for(char c = 'a'; c <= 'z'; c++) {
                int nextPos = dp[c - 'a'][pos]; // 尝试选择 nextPos
                if(nextPos == -1) continue;
                
                ans.push_back(c);
                if(c == letter) {
                    preNum++;
                }
                
                // printf("i=%d c=%c nextPos=%d ans=%s preNum=%d check=%d\n", i, c, nextPos, ans.c_str(), preNum, Check(nextPos + 1));
                
                if(Check(nextPos + 1)) {
                    // 有答案
                    pos = nextPos + 1;
                    break;
                }
                
                if(c == letter) {
                    preNum--;
                }
                ans.pop_back();
            }
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
