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
// unordered_map / unordered_set

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

int nums[500010][3];
class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size();
        memset(nums, -1, sizeof(int) * 3 * n);
        
        n--;
        nums[n][0] = nums[n][1] = nums[n][2] = 0;
        for(int i = n - 1; i >= 0; i--){
            int pos = obstacles[i] - 1;
            
            int minNum = 500010;
            for(int j = 0; j < 3; j++){
                if(j == pos){
                    nums[i][j] = -2; // 当前节点不可达
                    continue;
                }
                if(nums[i + 1][j] >= 0){
                    nums[i][j] = nums[i + 1][j];
                    minNum = min(minNum, nums[i][j]);
                } else {
                    nums[i][j] = -3; //前方有障碍物
                }
            }
            
            for(int j = 0; j < 3; j++){
                if(nums[i][j] == -3){
                    nums[i][j] = minNum + 1;
                }
            }
        }
        return nums[0][1];
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
