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


int dp[30][30][30][2]; // {min, max}


class Solution {
    void MyMin(int &a, int b){
        if(a == -1) {
            a = b;
        }
        a = min(a, b);
    }
    void MyMax(int &a, int b){
        if(a == -1) {
            a = b;
        }
        a = max(a, b);
    }
    void Update(int& a, int b, int flag){
        if(flag == 0){
            MyMin(a, b);
        }else{
            MyMax(a, b);
        }
    }
    int debug = 0;
    int dfs(const int n, const int a, const int b, const int flag){ // 1 <= a < b <=n
        if(dp[n][a][b][flag] != -1) return dp[n][a][b][flag];
        
        const int up_i = 1, up_n = n/2;
        int down_i = up_n + 1, down_n = n;
        int mid_flag = 0;
        
        if(n % 2 == 1){
            down_i++;
            mid_flag = 1;  
        }
        if(debug)printf("mid_flag=%d up_i=%d up_n=%d down_i=%d down_n=%d n=%d a=%d b=%d flag=%d\n", mid_flag, up_i, up_n, down_i, down_n, n, a, b, flag);
            
        if(mid_flag && b == up_n + 1){ // b 在中间
            int left_max = a - up_i;
            int mid_max = b - a - 1;
            int right_max = 0;
            
           if(debug)printf("mid_flag & b: left_max=%d mid_max=%d right_max=%d n=%d a=%d b=%d flag=%d\n", left_max, mid_max, right_max, n, a, b, flag);
            for(int left_i = 0; left_i <= left_max; left_i++){
                for(int mid_i = 0; mid_i <= mid_max; mid_i++){
                    int new_a = left_i + 1;
                    int new_b = left_i + mid_i + 2;
                    int new_n = up_n + mid_flag;
                    Update(dp[n][a][b][flag], dfs(new_n, new_a, new_b, flag) + 1, flag);
                }
            }
           if(debug)printf("b mid: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, dp[n][a][b][flag]);
            return dp[n][a][b][flag];
        }
            
        if(mid_flag && a == up_n + 1) { // a 在中间
            int left_max = down_n - b ;
            int mid_max = b - down_i;
            int right_max = 0;
            
           if(debug)printf("mid_flag & a: left_max=%d mid_max=%d right_max=%d n=%d a=%d b=%d flag=%d\n", left_max, mid_max, right_max, n, a, b, flag);
            for(int left_i = 0; left_i <= left_max; left_i++){
                for(int mid_i = 0; mid_i <= mid_max; mid_i++){
                    int new_a = left_i + mid_i + 1;
                    int new_b = left_i + mid_max + 2;
                    int new_n = up_n + mid_flag;
                    Update(dp[n][a][b][flag], dfs(new_n, new_a, new_b, flag) + 1, flag);
                }
            }
            if(debug)printf("a mid: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, dp[n][a][b][flag]);
            return dp[n][a][b][flag];
        }
            
        if(b <= up_n){ // 都在上侧, 不需要关心 mid_flag 和 right_max
            int left_max = a - up_i;
            int mid_max = b - a - 1;
            int right_max = up_n - b;
            if(debug)printf("b <= up_n: left_max=%d mid_max=%d right_max=%d n=%d a=%d b=%d flag=%d\n", left_max, mid_max, right_max, n, a, b, flag);

            for(int left_i = 0; left_i <= left_max; left_i++){
                for(int mid_i = 0; mid_i <= mid_max; mid_i++){
                    int new_a = left_i + 1;
                    int new_b = left_i + mid_i + 2;
                    int new_n = up_n + mid_flag;
                    Update(dp[n][a][b][flag], dfs(new_n, new_a, new_b, flag) + 1, flag);
                }
            }
            if(debug)printf("b <= up_n: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, dp[n][a][b][flag]);
            return dp[n][a][b][flag];
        }
            
        if(a >= down_i){ // 都在下侧，偏移量 和 大小都加 1
            int left_max = down_n - b; 
            int mid_max = b - a - 1;
            int right_max = a - down_i;
            if(debug)printf("a >= down_i: left_max=%d mid_max=%d right_max=%d n=%d a=%d b=%d flag=%d\n", left_max, mid_max, right_max, n, a, b, flag);

            for(int left_i = 0; left_i <= left_max; left_i++){
                for(int mid_i = 0; mid_i <= mid_max; mid_i++){
                    for(int right_i = 0; right_i <= right_max; right_i++){
                        int new_a = left_i + mid_i + right_max + 1 + mid_flag;
                        int new_b = left_i + mid_max + right_max + 2 + mid_flag;
                        
                        
                        int new_n = up_n + mid_flag;
                        Update(dp[n][a][b][flag], dfs(new_n, new_a, new_b, flag) + 1, flag);
                    }
                }
            }
           if(debug)printf("a >= down_i: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, dp[n][a][b][flag]);
            return dp[n][a][b][flag];
        }
            
        // // a 在上侧，b 在下侧，计算出偏移量
        int up_a = a - up_i + 1;
        int down_b = up_n - (b - down_i + 1) + 1;
        
        if(debug)printf("up_a=%d down_b=%d\n", up_a, down_b);
        if(up_a == down_b){
           if(debug)printf("up_a == down_b: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, 1);
            return dp[n][a][b][flag] = 1;
        }
            
        if(up_a < down_b){ //
            int left_max = a - up_i;
            int mid_max = down_b - up_a - 1;
            int right_max = b - down_i;
            
           if(debug)printf("up_a < down_b: left_max=%d mid_max=%d right_max=%d n=%d a=%d b=%d flag=%d\n", left_max, mid_max, right_max, n, a, b, flag);
            for(int left_i = 0; left_i <= left_max; left_i++){
                for(int mid_i = 0; mid_i <= mid_max; mid_i++){
                    for(int right_i = 0; right_i <= right_max; right_i++){
                        int new_a = left_i + 1;
                        int new_b = left_i + mid_i + right_max + 2 + mid_flag;
                        int new_n = up_n + mid_flag;
                        Update(dp[n][a][b][flag], dfs(new_n, new_a, new_b, flag) + 1, flag);
                    }
                }
            }
            if(debug)printf("up_a < down_b: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, dp[n][a][b][flag]);
            return dp[n][a][b][flag];
        }else{
            int left_max = down_n - b;
            int mid_max = up_a - down_b - 1;
            int right_max = up_n - a;

            if(debug)printf("up_a > down_b left_max=%d mid_max=%d right_max=%d n=%d a=%d b=%d flag=%d\n", left_max, mid_max, right_max, n, a, b, flag);
             for(int left_i = 0; left_i <= left_max; left_i++){
                 for(int mid_i = 0; mid_i <= mid_max; mid_i++){
                      for(int right_i = 0; right_i <= right_max; right_i++){
                          int new_a = left_i + mid_i + 1;
                          int new_b = left_i + mid_max + right_max + 2 + mid_flag;
                          int new_n = up_n + mid_flag;
                          Update(dp[n][a][b][flag], dfs(new_n, new_a, new_b, flag) + 1, flag);
                      }
                 }
             }

            if(debug)printf("up_a > down_b: n=%d a=%d b=%d flag=%d ans=%d\n", n, a, b, flag, dp[n][a][b][flag]);
            return dp[n][a][b][flag];
        }
    }
public:
    vector<int> earliestAndLatest(int n, int a, int b) {
        memset(dp, -1, sizeof(dp));
        vector<int> ans;
        ans.push_back(dfs(n, a, b, 0));
        ans.push_back(dfs(n, a, b, 1));
        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
