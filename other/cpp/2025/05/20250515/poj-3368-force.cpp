/*
Description

You are given a sequence of n integers a1 , a2 , ... , an in non-decreasing order. In addition to that, you are given
several queries consisting of indices i and j (1 ≤ i ≤ j ≤ n). For each query, determine the most frequent value among
the integers ai , ... , aj.

Input

The input consists of several test cases. Each test case starts with a line containing two integers n and q (1 ≤ n, q ≤
100000). The next line contains n integers a1 , ... , an (-100000 ≤ ai ≤ 100000, for each i ∈ {1, ..., n}) separated by
spaces. You can assume that for each i ∈ {1, ..., n-1}: ai ≤ ai+1. The following q lines contain one query each,
consisting of two integers i and j (1 ≤ i ≤ j ≤ n), which indicate the boundary indices for the query.

The last test case is followed by a line containing a single 0.

Output

For each query, print one line with one integer: The number of occurrences of the most frequent value within the given
range.
*/
#include <math.h> /* log2 */

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
const int N = 100011;
int F[N][20];
int a[N], cnt[N], n, q, k, l, r;
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    // printf("%d\n", a[i]);
  }
  // printf("1->%d\n", a[1]);
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &l, &r);
    // printf("l=%d r=%d\n", l, r);
    // for(int j=l;j<=r;j++){
    //   printf("j=%d %d\n", j, a[j]);
    // }
    // 找到区间 [l, r] 中第一个不同值的位置
    int maxFreq = 1;
    int pre = a[l];
    int cnt = 0;
    int t = l;
    while (t <= r) {
      if (pre != a[t]) {
        cnt = 0;
        pre = a[t];
      }
      cnt++;
      maxFreq = max(maxFreq, cnt);
      t++;
    }
    printf("%d %d %d\n", l, r, maxFreq);
  }
  return 0;
}
/*
6 3
1 7 3 4 2 5
1 5
4 6
2 2



6
3
0
*/
