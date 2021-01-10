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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
class Solution {
    vector<int> flag;
    vector<int> source;
    vector<int> target;
    int n;
    
    vector<vector<int>> edges;
    
    unordered_map<int, int> m;
    
    int ans ;
    void add(int v){
        auto it = m.find(v);
        if(it == m.end()){
            m[v] = 1;
            return;
        }
        
        if(it->second > 0){
            it->second++;
        }else if(it->second < 0){
            it->second++;
            ans++; // 匹配一组
        }else{
            it->second++;
        }
    }
    void del(int v){
        auto it = m.find(v);
        if(it == m.end()){
            m[v] = -1;
            return;
        }
        
        if(it->second > 0){
            it->second--;
            ans++; //匹配一组
        }else if(it->second < 0){
            it->second--;
        }else{
            it->second--;
        }
    }
    
    void dfs(int a){
        if(flag[a]) return ;
        flag[a] = 1;
        //printf("i:%d s=%d t=%d\n", a, source[a], target[a]);
        add(source[a]);
        del(target[a]);
        
        
        for(auto v: edges[a]){
            dfs(v);
        }
    }
    
public:
    int minimumHammingDistance(vector<int>& source_, vector<int>& target_, vector<vector<int>>& allowedSwaps) {
        source.swap(source_);
        target.swap(target_);
        
        n = source.size();
        flag.resize(n, 0);
        edges.resize(n);
        
        for(auto& e: allowedSwaps){
            edges[e[0]].push_back(e[1]);
            edges[e[1]].push_back(e[0]);
        }
        
        ans = 0;
        for(int i=0;i<n;i++){
            if(flag[i] == 1) continue;
            m.clear();
            //printf("group: \n");
            dfs(i);
        }
        
        return n - ans;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
