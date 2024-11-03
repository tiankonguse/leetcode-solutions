/*
ID: tiankonguse
TASK: D
LANG: C++
*/
#define TASK "A"

#include <bits/stdc++.h>

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
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
  ll num = 0;

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
  while (numsSearch.size() < ansNum) {
    numsSearch.push_back(val);
  }
  sort(numsSearch.begin(), numsSearch.end());
  for (int i = 0; i < ansNum; i++) {
    printf("%lld%c", numsSearch[i], i + 1 == ansNum ? '\n' : ' ');
  }
  // printf("SearchFirst L=%lld R=%lld RV=%lld\n", L, R, val);
  return val;
}

// void TestLeqR() {
//   // 暴力检查答案是否正确 L == R
//   /*
//     12 1 1
//     1 1 3 3 5 5 6 6 8 8 9 9
//     2 2 3 3 4 4 5 5 6 6 7 7
//    */
//   ll disNum = 0;
//   for (int i = 1; i <= n * n; i++) {
//     const ll L = i;
//     const ll R = i;

//     ll ans1 = ForceSort(L, R);
//     ll ans2 = SearchLR(L, R);
//     if (ans1 != ans2) {
//       disNum++;
//       printf("L=R=%d ans1=%lld ans2=%lld\n", i, ans1, ans2);
//       break;
//     }
//   }
//   printf("disNum=%lld\n", disNum);
// }

// bool EQ(const vector<ll>& nums1, const vector<ll>& nums2) {
//   if (nums1.size() != nums2.size()) {
//     printf("size diff:  size1=%d size2=%d\n", int(nums1.size()),
//            int(nums2.size()));
//     return false;
//   }
//   for (int i = 0; i < nums1.size(); i++) {
//     if (nums1[i] == nums2[i]) continue;
//     printf("diff pos=%d v1=%lld v2=%lld size1=%d size2=%d\n", i, nums1[i],
//            nums2[i], int(nums1.size()), int(nums2.size()));
//     return false;
//   }
//   return true;
// }

// void testLeqOne() {
//   // 暴力检查答案是否正确 L=1
//   /*
//     12 1 1
//     1 1 3 3 5 5 6 6 8 8 9 9
//     2 2 3 3 4 4 5 5 6 6 7 7

//     7 1 1
//     1 1 3 3 5 5 6
//     2 2 3 3 4 4 5

//    */
//   ll disNum = 0;
//   for (int i = 1; i <= n * n; i++) {
//     const ll L = 1;
//     const ll R = i;
//     ll ans1 = ForceSort(L, R);
//     ll ans2 = SearchFirst(L, R);
//     if (!EQ(numsForce, numsSearch)) {
//       // printf("L=%lld R=%lld ans1=%lld ans=%lld\n", L, R, ans1, ans2);
//       disNum++;
//       break;
//     }
//   }
//   printf("disNum=%lld\n", disNum);
// }

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

  if (n < 5000) {
    ForceSort(L, R);
    return;
  }
  if (L == R) {
    SearchLR(L, R);
    return;
  }
  if (L == 1) {
    SearchFirst(L, R);
    return;
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

// int dir[4][2] = {{-1, +1}, {0, 1}, {1, -1}, {+1, 0}};
// void SearchFirst() {  // 一个个搜索
//   int x = 0, y = 0;
//   ll nowSum = A[0] + B[0];
//   // 枚举规则：
//   // 1) [x-1, y + 1]
//   // 2) [x, y + 1]
//   // 3) [x+1, y-1]
//   // 4) [x+1, y]
//   printf("%lld", nowSum);
//   ll maxSum = A[n - 1] + B[n - 1] + 1;

//   for (int i = 1; i < R; i++) {
//     ll newSum = maxSum;
//     for (int k = 0; k < 4; k++) {
//       int X = x + dir[k][0];
//       int Y = y + dir[k][1];
//       if (X < 0 || Y < 0 || X == n || Y == n) {
//         continue;
//       }
//       ll newSum = A[X] + A[Y];
//       if(newSum < nowSum){
//         continue; // 小的忽略
//       }
//       if (newSum == nowSum && X < x) {
//         continue;  // 值相等，判断相对位置, X 不能后退，避免重复
//       }

//     }
//   }
//   printf("\n");
// }