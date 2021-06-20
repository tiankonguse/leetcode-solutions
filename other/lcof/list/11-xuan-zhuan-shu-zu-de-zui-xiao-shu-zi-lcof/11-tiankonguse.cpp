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


class Solution {

    int Search(vector<int>& vec, int l, int r){
        if(r - l <= 2){ // 一个或者两个
            return min(vec[l], vec[r-1]);
        }

        int ans = vec[l];
        while(l < r){
            if(vec[l] < vec[r - 1]){ // 升序
                ans = min(ans, vec[l]);
                break;
            }
            if(l + 1 == r){ // 剩余最后一个
                ans = min(ans, vec[l]);
                break;
            }

            int mid = (l + r)/2;
            ans = min(ans, vec[mid]);
            
            if(vec[mid] > vec[l]) {
                l = mid + 1;
                ans = min(ans, vec[l]);
            }else if(vec[mid] < vec[l]){ // mid 是最小值，之后就是升序了
                r = mid;
            }else{ // 相等，可能在左半部，也可能在右半部。 假设在左半部
                ans = min(ans, Search(vec, l, mid));
                l = mid + 1;
            }
        }
        return ans;
    }

public:
    int minArray(vector<int>& vec) {
        return Search(vec, 0, vec.size());
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
