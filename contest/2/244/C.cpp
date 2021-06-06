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


const int max5 = 100100;
int pre[2][max5];
int next_val[2][max5];

class Solution {
    int n;
    
    int Cal(const char* s, int n, char first_val){
        int ans = 0;
        
        int v = first_val - '0';
        for(int i=0;i<n;i++){
            if(s[i] != '0' + v){
                ans++;
            }
            v = 1 - v;
        }
        
        return ans;
    }
    
    int Trans(string& s){
        
        // 前缀预处理
        for(int flag = 0; flag <= 1; flag++){
            int v = flag;
            pre[flag][0] = 0;
            for(int i=1;i<=n;i++){
                if(s[i-1] != '0' + v){
                    pre[flag][i] = pre[flag][i-1] + 1;
                }else{
                    pre[flag][i] = pre[flag][i-1];
                }
                 v = 1 - v;
            }
        }
        
        // 后缀预处理
        for(int flag = 0; flag <= 1; flag++){
            int v = flag;
            next_val[flag][n+1] = 0;
            for(int i=n;i>=1;i--){
                if(s[i-1] != '0' + v){
                    next_val[flag][i] = next_val[flag][i+1] + 1;
                }else{
                    next_val[flag][i] = next_val[flag][i+1];
                }
                 v = 1 - v;
            }
        }
        
        // 找中界限
        int ans = n;
        for(int i=1;i<n;i++){
            // [1, i], [i+1, n]
            ans = min(ans, pre[0][i] + next_val[1][i+1]);
            ans = min(ans, pre[1][i] + next_val[0][i+1]);
        }
        
        return ans;
    }
    
public:
    int minFlips(string& s) {
        
        n = s.size();
        if(n == 1){
            return 0;
        }
        
        int ans = n;
        ans = min(ans, Cal(s.c_str(), n, '0'));
        ans = min(ans, Cal(s.c_str(), n, '1'));
        
        // 左移一下
        ans = min(ans, Trans(s));
        
        
        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
