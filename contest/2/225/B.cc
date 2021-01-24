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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
class Solution {
    map<char, int> ma, mb;
    int la, lb;
    int ans;
        

    
    int EqOne(char c){
        int num = 0;
        if(ma.count(c) == 0){
            num += la;
        }else{
            num += la - ma[c];
        }
        
        if(mb.count(c) == 0){
            num += lb;
        }else{
            num += lb - mb[c];
        }
        return num;
    }
    int Little(char c, map<char, int>&maa, map<char, int>&mbb){
        // 左边的为 'a'~c， 右边的为 c+1 ~ 'z'
        
        if(c == 'z'){
            return ans;
        }
        
        int num = 0;
        for(auto p: maa){
            if(p.first > c){
                num += p.second;
            }
        }
        
        for(auto p: mbb){
            if(p.first <= c){
                num += p.second;
            }
        }
        return num;
    }
    
public:
    int minCharacters(string& a, string& b) {
        la = a.length();
        lb = b.length();
        ans = la + lb;
        
        for(auto c: a) ma[c]++;
        for(auto c: b) mb[c]++;
        for(char c = 'a'; c <= 'z'; c++){
            ans = min(ans, EqOne(c));
            ans = min(ans, Little(c, ma, mb));
            ans = min(ans, Little(c, mb, ma));
        }
        
        
        return ans;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
