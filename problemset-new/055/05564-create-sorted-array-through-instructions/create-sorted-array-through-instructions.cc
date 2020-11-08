#include "base.h"


typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >;
template <class T>
using max_queue = priority_queue<T>;

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class TreeArray {
 public:
  void init(int n_) {
    n = n_;
    memset(c, 0, sizeof(ll) * (n + 2));
  }

  ll query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll query(int l, int r) { 
      if(l > r) return 0;
      return query(r) - query(l - 1); 
  }

  void add(int x, ll v) {
    while (x <= n) {
      c[x] += v;
      x += Lowbit(x);
    }
  }

 private:
  int Lowbit(int x) { return x & -x; }
  ll c[max5];
  int n;
};

TreeArray treeArray;

class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        ll ans = 0;
        
        int n = 100000;
        treeArray.init(n);
        
        for(auto v: instructions){
            ll left = treeArray.query(1, v-1);
            ll right = treeArray.query(v+1, n);
            treeArray.add(v, 1);
            ans += min(left, right);
            ans %= mod;
        }
        
        return ans;
    }
};

int main() {
    TEST_SMP1(Solution, createSortedArray, 1, vector<int>({1,5,6,2}));
    TEST_SMP1(Solution, createSortedArray, 3, vector<int>({1,2,3,6,5,4}));
    TEST_SMP1(Solution, createSortedArray, 4, vector<int>({1,3,3,3,2,4,2,1,2}));

    return 0;
}