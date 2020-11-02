#include <bits/stdc++.h>
using namespace std;

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
const int max3 = 2100, max4 = 11100, max5 = 55000, max6 = 2000100;

class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    memset(c, 0, sizeof(ll) * (n + 2));
  }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) { return Query(r) - Query(l - 1); }

  void Add(int x, ll v) {
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

class NumArray {
vector<int> nums_;
public:
    NumArray(vector<int>& nums) {
        nums_.swap(nums);

        treeArray.Init(nums_.size() + 1);
        for(int i=0;i<nums_.size();i++){
            treeArray.Add(i+1, nums_[i]);
        }
    }
    
    void update(int i, int val) {
        treeArray.Add(i+1, val - nums_[i]);
        nums_[i] = val;
    }
    
    int sumRange(int i, int j) {
        return treeArray.Query(i+1, j+1);
    }
};

int main() {

  return 0;
}