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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

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

class Solution {
public:
    int storeWater(vector<int>& bucket, vector<int>& vat) {
        if(accumulate(vat.begin(), vat.end(), 0) == 0){
            return 0;
        }
        
        int preAns = 0;
        int n = bucket.size();
        
        
        for(int i=0;i<n;i++){
            if(vat[i] > 0 && bucket[i] == 0){
                preAns++;
                bucket[i]++;
            }
        }
        
        
        //printf("base = %d\n", ans);
        
        map<int, int> m; // 计数优化
        max_queue<pair<int, int>> que; // 贪心队列
        
        for(int i=0;i<n;i++){
            if(vat[i] == 0) continue;
            int num = (vat[i] + bucket[i] - 1)/bucket[i];
            if(num > 1){
                que.push({num, i});
            }
            m[num]++;
        }
        
        int ans = preAns + m.rbegin()->first;
        while(!que.empty()){
            auto p = que.top();que.pop();
            int num = p.first, i = p.second;
            int tmpNum = num - 1;
            int want = (vat[i] + tmpNum - 1)/tmpNum;
            
            preAns += want - bucket[i];
            bucket[i] = want;
            
            m[num]--;
            if(m[num] == 0){
                m.erase(num);
            }
            
        
            if(tmpNum > 1){
                que.push({tmpNum, i});
            }
            m[tmpNum]++;
            
            int maxNum = m.rbegin()->first;
            ans = min(ans, preAns + maxNum);
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
