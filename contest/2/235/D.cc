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

const int N = 2 * 100100;
const int M = 30000;
bool is[N];
int prm[M];

int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
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

vector<int> m[N];
pair<int, int> tmpPrm[N];
int tmp_prm_num;

class Solution {
  int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

  int max_val = 0;

  void init(vector<int>& nums) {
    int prmNum = getprm();

    for (const auto v : nums) {
        max_val = max(max_val, v);
    }
    for(int i=0;i<=max_val;i++){
        m[i].clear();
    }
      
    for (const auto v : nums) {
      int tmpVal = v;
      
      tmp_prm_num = 0;
      for (int i = 0; i < prmNum; i++) {
        if (is[tmpVal] || tmpVal == 1) {  //剪枝
          tmpPrm[tmp_prm_num++] = {tmpVal, 1};
          break;
        }

        if (tmpVal % prm[i] != 0) continue;

        int num = 0;
        while (tmpVal % prm[i] == 0) {
          num++;
          tmpVal /= prm[i];
        }
        tmpPrm[tmp_prm_num++] = {prm[i], num};
      }
      dfs(0, 1, v);
    }
  }

  void dfs(int pos, int ans, int baseVal) {
    if (pos == tmp_prm_num) {
        m[ans].push_back(baseVal);
        return;
    }
    const auto& [val, num] = tmpPrm[pos];

    int pow_val = 1;
    for (int i = 0; i <= num; i++) { // 排列组合求出所有约数
        dfs(pos + 1, ans * pow_val,  baseVal);
        if(i < num){
            pow_val *= val; //最后一次，不需要计算了
        }
    }
  }

  bool check(const vector<int>& s, int want_val) {
    int val = 0;
    for (auto v : s) {
      if (val == 0) {
        val = v;
      } else {
        val = gcd(val, v);
      }
      if (val == want_val) {
        break;
      }
    }
    return val == want_val;
  }

 public:
  int countDifferentSubsequenceGCDs(vector<int>& nums_) {
    init(nums_);
    int ans = 0;
    for (int i = 1; i <= max_val; i++) {
      if (m[i].size() == 0) continue;
      if (check(m[i], i)) {
        ans++;
      }
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
