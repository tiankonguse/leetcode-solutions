/*
ID: tiankonguse
TASK: D
LANG: C++
*/
#define TASK "D"

#include <bits/stdc++.h>

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

using namespace std;
typedef long long ll;

void InitIO() {
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n;
vector<ll> A;
vector<ll> B;

vector<ll> numsForce;
ll ForceSort(const ll L, const ll R) {
  vector<ll> numsAll;
  numsAll.clear();
  numsAll.reserve(n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      numsAll.push_back(A[i] + B[j]);
    }
  }
  sort(numsAll.begin(), numsAll.end());
  numsForce.clear();
  numsForce.reserve(R - L + 1);
  for (int i = L - 1; i < R; i++) {
    numsForce.push_back(numsAll[i]);
    printf("%lld%c", numsAll[i], i + 1 == R ? '\n' : ' ');
  }
  // printf("ForceSort L=%lld R=%lld RV=%lld\n", L, R, numsForce.back());
  return numsForce.back();
}
ll BinarySearch(const ll R) {  // 只能查找 R
  ll l = 1, r = A[n - 1] + B[n - 1] + 1;
  while (l < r) {
    ll mid = (l + r) / 2;
    ll numAll = 0;
    for (int a = 0; a < n; a++) {  // 找 <= mid 的个数
      const ll av = A[a];
      const ll bv = mid - av;
      const ll num = upper_bound(B.begin(), B.end(), bv) - B.begin();
      numAll += num;
    }
    if (numAll < R) {  // 不够
      l = mid + 1;
    } else if (numAll >= R) {  // 恰好找到 L 个, mid 处于空洞里时也满足
      r = mid;
    }
  }
  // printf("BinarySearch R=%lld RV=%lld\n", R, l);
  return l;
}
ll SearchLR(const ll L, const ll R) {
  ll v = BinarySearch(R);
  printf("%lld\n", v);
  return v;
}

vector<ll> numsSearch;
ll SearchFirst(const ll L, const ll R) {
  const ll val = BinarySearch(R);

  ll ansNum = R - L + 1;
  numsSearch.clear();
  numsSearch.reserve(ansNum);
  for (int i = 0; i < n; i++) {
    if (A[i] > val) break;  // 剪枝
    for (int j = 0; j < n; j++) {
      const ll sum = A[i] + B[j];
      if (sum >= val) break;  // 极端情况下所有 A 和 B 都相等，相等的可能很多
      numsSearch.push_back(sum);
    }
  }
  while (ll(numsSearch.size()) < ansNum) {
    numsSearch.push_back(val);
  }
  sort(numsSearch.begin(), numsSearch.end());
  for (ll i = 0; i < ansNum; i++) {
    printf("%lld%c", numsSearch[i], i + 1 == ansNum ? '\n' : ' ');
  }
  // printf("SearchFirst L=%lld R=%lld RV=%lld\n", L, R, val);
  return val;
}

void TestLeqR() {
  // 暴力检查答案是否正确 L == R
  /*
    12 1 1
    1 1 3 3 5 5 6 6 8 8 9 9
    2 2 3 3 4 4 5 5 6 6 7 7
   */
  ll disNum = 0;
  for (int i = 1; i <= n * n; i++) {
    const ll L = i;
    const ll R = i;
    ll ans1 = ForceSort(L, R);
    ll ans2 = SearchLR(L, R);
    if (ans1 != ans2) {
      disNum++;
      printf("L=R=%d ans1=%lld ans2=%lld\n", i, ans1, ans2);
      break;
    }
  }
  printf("disNum=%lld\n", disNum);
}

bool EQ(const vector<ll>& nums1, const vector<ll>& nums2) {
  if (nums1.size() != nums2.size()) {
    printf("size diff:  size1=%d size2=%d\n", int(nums1.size()),
           int(nums2.size()));
    return false;
  }
  for (size_t i = 0; i < nums1.size(); i++) {
    if (nums1[i] == nums2[i]) continue;
    printf("diff pos=%d v1=%lld v2=%lld size1=%d size2=%d\n", int(i), nums1[i],
           nums2[i], int(nums1.size()), int(nums2.size()));
    return false;
  }
  return true;
}

void testLeqOne() {
  // 暴力检查答案是否正确 L=1
  /*
    12 1 1
    1 1 3 3 5 5 6 6 8 8 9 9
    2 2 3 3 4 4 5 5 6 6 7 7
    7 1 1
    1 1 3 3 5 5 6
    2 2 3 3 4 4 5
   */
  ll disNum = 0;
  for (int i = 1; i <= n * n; i++) {
    const ll L = 1;
    const ll R = i;
    ll ans1 = ForceSort(L, R);
    ll ans2 = SearchFirst(L, R);
    if (!EQ(numsForce, numsSearch)) {
      printf("L=%lld R=%lld ans1=%lld ans=%lld\n", L, R, ans1, ans2);
      disNum++;
      break;
    }
  }
  printf("disNum=%lld\n", disNum);
}

// 输入 sum，找到最左边界
ll BinarySearchByValue(ll V) {  //
  ll l = 1, r = n * n + 1;
  while (l < r) {
    ll mid = (l + r) / 2;
    ll midV = BinarySearch(mid);
    if (midV < V) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l;
}

vector<ll> numsOther;
ll SearchOther(const ll L, const ll R) {  //
  const ll ansNum = R - L + 1;
  numsOther.clear();
  numsOther.reserve(ansNum);

  ll LV = BinarySearch(L);  // n log(n) log(n)
  ll RV = BinarySearch(R);  // n log(n) log(n)
  // printf("SearchOther L=%lld R=%lld LV=%lld RV=%lld\n", L, R, LV, RV);

  // 值为 LV 或者 RV 的可能很多，所以先搜索  (Lv, Rv) 范围的答案
  for (int i = 0; i < n; i++) {
    const ll lv_a = LV - A[i];  // 目标查找 a+b>LV 的第一个位置
    auto j = upper_bound(B.begin(), B.end(), lv_a) - B.begin();
    while (j < n && A[i] + B[j] < RV) {
      numsOther.push_back(A[i] + B[j]);
      j++;
    }
  }

  // 找到 LV 的右边界
  ll LR = BinarySearchByValue(LV + 1) - 1;  // 二分找到 LV 的右边界
  for (ll i = L; i <= R && i <= LR; i++) {
    numsOther.push_back(LV);
  }
  while (ll(numsOther.size()) < ansNum) {
    numsOther.push_back(RV);  // 剩下的就是右边界
  }

  sort(numsOther.begin(), numsOther.end());
  for (ll i = 0; i < ansNum; i++) {
    printf("%lld%c", numsOther[i], i + 1 == ansNum ? '\n' : ' ');
  }

  return RV;
}

void testRange() {
  // 暴力检查答案是否正确 [L,R]
  /*
    12 1 1
    1 1 3 3 5 5 6 6 8 8 9 9
    2 2 3 3 4 4 5 5 6 6 7 7
    7 1 1
    1 1 3 3 5 5 6
    2 2 3 3 4 4 5
   */
  ll disNum = 0;
  for (int i = 1; i <= n * n; i++) {
    for (int j = i; j <= n * n; j++) {
      const ll L = i;
      const ll R = j;
      ll ans1 = ForceSort(L, R);
      ll ans2 = SearchOther(L, R);
      if (!EQ(numsForce, numsOther)) {
        printf("L=%lld R=%lld ans1=%lld ans=%lld\n", L, R, ans1, ans2);
        disNum++;
        break;
      }
    }
  }
  printf("disNum=%lld\n", disNum);
}

void Solver() {  //
  ll L, R;
  scanf("%lld%lld%lld", &n, &L, &R);
  A.resize(n);
  B.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &A[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%lld", &B[i]);
  }
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  // 暴力检查答案是否正确 L == R
  // TestLeqR();
  // return;

  // 暴力检查答案是否正确 L == 1
  // testLeqOne();
  // return;

  // 暴力检查答案是否正确 任意情况
  // testRange();
  // return;

  if (n < 5000) {
    ForceSort(L, R);
  } else if (L == R) {
    SearchLR(L, R);
  } else if (L == 1) {
    SearchFirst(L, R);
  } else {
    SearchOther(L, R);
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
12
1 1 3 3 5 5 6 6 8 8 9 9
2 2 3 3 4 4 5 5 6 6 7 7

*/
