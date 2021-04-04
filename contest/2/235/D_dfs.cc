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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 21100, max5 = 200100, max6 = 2000100;

/*
筛素数
*/

const int N = 100100;
const int M = 30000;
bool is[N];
int prm[M];
int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 1;
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return k;
}

class Solution {
    int gcd(int x, int y){
        return y==0?x:gcd(y,x%y);
    }
    
    unordered_set<int> gcds;
    vector<int> nums;
    int n;
    int min_prm_val = 1; // 
    int min_prm_index = 0;
    int max_prm;
    set<pair<int,int>> cache;
    
    void init(vector<int>& nums_){
        nums.swap(nums_);
        
        set<int> s;
        for(auto v: nums){
            s.insert(v);
        }
        
        nums.clear();
        for(auto v: s){
            nums.push_back(v);
        }
        
        n = nums.size();
        
        max_prm = getprm();
    }
    
    void updateAns(int v){
        if(gcds.count(v)){
            return;
        }
        
        //printf("add ans=%d\n", v);
        gcds.insert(v);
        
        while(gcds.count(min_prm_val)){
            min_prm_index++;
            min_prm_val = prm[min_prm_index];
        }
        
    }
    
    void dfs(const int pos, const int val){
        //printf("pos=%d val=%d min_prm_val = %d\n", pos, val, min_prm_val);
        if(pos == n){
            return ; // 出口
        }
        if(val > 0 && val < min_prm_val){
            return; // 小于 val 的素数都已经是答案了，剪枝
        }
        pair<int, int> p = {pos, val};
        
        if(cache.count(p)){
            return; // 剪枝
        }
        
        cache.insert(p);
        
        // 选择 pos
        int select_val = val;
        if(select_val == 0){
            select_val = nums[pos];
        }else{
            select_val = gcd(select_val, nums[pos]);
        }
        //printf("select pos=%d, val = %d\n",  pos, select_val);
        updateAns(select_val);
        dfs(pos+1, select_val);
        
        // 不选择
         //printf("not select pos=%d, val = %d\n",  pos, val);
         dfs(pos+1, val);
    }
    
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums_) {
        init(nums_);
        for(auto v: nums){
            updateAns(v);
        }
        dfs(0, 0);
        return gcds.size();
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
