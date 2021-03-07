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
// reserve
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll mod = 1000000007;

class Solution {
    vector<ll> disVals; // 到 n 的权重
    vector<vector<pair<int, ll>>> m;
    vector<ll> ans; 
    vector<ll> inDeg; //入度
    int n;
    
    void ResetInDeg(){
        inDeg.resize(n+1, 0);
        for(int i=1;i<=n;i++){
            for(auto&p : m[i]){
                inDeg[p.first]++;
            }
        }
    }
    
    
    
    void BfsVal(){ 
        disVals.resize(n+1, INF);
        
        min_queue<pair<ll, int>> que;
        que.push({0, n});
        
        unordered_set<int> s;
        while(!que.empty()){
            auto node = que.top(); que.pop();
            int u = node.second;
            
            if(s.count(u))continue; 
            disVals[u] = node.first; // 找到 u 的最优单
            s.insert(u);
            //printf("u=%d v=%lld\n", u, disVals[u]);
                    
            for(auto&p : m[u]){
                int v = p.first;
                if(s.count(v)) continue;
                
                ll newVal = disVals[u] + p.second; 
                if(newVal < disVals[v]){
                    que.push({newVal, v}); // 有更优答案
                }
            }
        }
    }
    
    void BfsAns(){
        min_queue<pair<ll, int>> que;
        for(int i=1;i<=n;i++){
            que.push({disVals[i], i});
        }
        
        ans.resize(n+1, 0);
        ans[n] = 1;
        
        while(!que.empty()){
            auto node = que.top(); que.pop();
            int u = node.second;
            
            for(auto&p : m[u]){
                int v = p.first;
                
                ans[u] = (ans[u] + ans[v]) % mod;
            }
            
        }
        
        
    }
    
public:
    int countRestrictedPaths(int n_, vector<vector<int>>& edges) {
        n = n_;
        m.resize(n+1);
        inDeg.resize(n+1, 0);
            
        for(auto& v: edges){
            m[v[0]].push_back({v[1], v[2]});
            m[v[1]].push_back({v[0], v[2]});
        }
        
        BfsVal();
        
        
        for(int i = 1; i <= n; i++){
            int u = i;
            auto& e = m[u];
            for(int j = 0; j < e.size(); j++){
                int v = e[j].first;
                
                if(disVals[u] <= disVals[v]){ // u 无法到达 v
                    swap(e[j], e.back());
                    e.pop_back();
                    j--;
                }
            }
        }
        
        BfsAns();
        
        return ans[1];
    }
};
int main() {
  // vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  // vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  // TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
