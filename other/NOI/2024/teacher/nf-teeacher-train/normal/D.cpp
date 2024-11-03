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

void InitIO() {
#ifdef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
}

const int N = 1e5 + 10;
int n;
int A[N];
int B[N];
int ans[N];
int ansIndex = 0;

int BinarySearch(int R) {  // 只能查找 R
  int l = 1, r = A[n - 1] + B[n - 1] + 1;
  while (l < r) {
    int mid = (l + r) / 2;
    int numAll = 0;
    for (int a = 0; a < n; a++) {  // 找 <= mid 的个数
      const int num = upper_bound(B, B + n, mid - A[a]) - B;
      numAll += num;
    }
    if (numAll < R) {  // 不够
      l = mid + 1;
    } else if (numAll >= R) {  // 恰好找到 L 个, mid 处于空洞里时也满足
      r = mid;
    }
  }
  return l;
}

// 输入 sum，找到最左边界
int BinarySearchByValue(int V) {  //
  int l = 1, r = n * n + 1;
  while (l < r) {
    int mid = (l + r) / 2;
    int midV = BinarySearch(mid);
    if (midV < V) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l;
}

int SearchOther(const int L, const int R) {  //
  const int ansNum = R - L + 1;

  int LV = BinarySearch(L);  // n log(n) log(n)
  int RV = BinarySearch(R);  // n log(n) log(n)
  if (L == R) {
    printf("%d\n", LV);
    return LV;
  }
  if (LV == RV) {
    for (int i = 0; i < ansNum; i++) {
      printf("%d%c", LV, i + 1 == ansNum ? '\n' : ' ');
    }
    return LV;
  }

  // 值为 LV 或者 RV 的可能很多，所以先搜索  (Lv, Rv) 范围的答案
  for (int i = 0; i < n; i++) {
    const int lv_a = LV - A[i];  // 目标查找 a+b>LV 的第一个位置
    auto j = upper_bound(B, B + n, lv_a) - B;
    while (j < n && A[i] + B[j] < RV) {
      ans[ansIndex++] = A[i] + B[j];
      j++;
    }
  }

  // 找到 LV 的右边界
  int LR = BinarySearchByValue(LV + 1) - 1;  // 二分找到 LV 的右边界
  for (int i = L; i <= R && i <= LR; i++) {
    ans[ansIndex++] = LV;
  }
  while (ansIndex < ansNum) {  // 剩下的就是右边界
    ans[ansIndex++] = RV;
  }

  sort(ans, ans + ansNum);
  for (int i = 0; i < ansNum; i++) {
    printf("%d%c", ans[i], i + 1 == ansNum ? '\n' : ' ');
  }

  return RV;
}

void Solver() {  //
  int L, R;
  scanf("%d%d%d", &n, &L, &R);
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &B[i]);
  }
  sort(A, A + n);
  sort(B, B + n);

  SearchOther(L, R);
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
