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


int dp[111111][111];

class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        
        int min_val = 100, max_val = 1;
        for(int i = 1; i <= n; i++){
            int v = nums[i-1];
            
            for(int j = min_val; j <= max_val; j++){
                dp[i][j] += dp[i-1][j];
            }
            
            min_val = min(min_val, v);
            max_val = max(max_val, v);
            dp[i][v]++;
        }
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for(auto& p: queries){
            int l = p[0] + 1;
            int r = p[1] + 1;
            
            int one_ans = -1;
            int pre_val = -1;
            for(int j = min_val; j <= max_val; j++){
                if(dp[r][j] == dp[l - 1][j]) continue;
                if(pre_val == -1){
                    pre_val = j;
                    continue;
                }
                if(one_ans == -1){
                    one_ans = j - pre_val;
                }else{
                    one_ans = min(one_ans, j - pre_val);
                }
                pre_val = j;
            }
            ans.push_back(one_ans);
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
