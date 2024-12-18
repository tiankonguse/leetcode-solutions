#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
long long a[N];       // 存储每根原木的长度
long long n;          // 原木数量
long long k;          // 小段数量
int check(int len) {  // 检验当前长度是否满足条件
  long long ct = 0;   // 小段的总数量
  long long num = 0;  // 表示每个原木能切的段数
  for (int i = 0; i < n; i++) {
    num = a[i] / len;  // 计算当前原木能切出的段数
    ct += num;         // 累加切出的段数
    if (ct >= k) {     // 如果当前总段数达到要求的段数
      return true;
    }
  }
  // 当都切完后得到的段数都没有达到要求的段数
  if (ct < k) return false;
}
int BinaryCheck(int L, int R) {
  int ans;
  while (L <= R) {
    int mid = (L + R) / 2;
    if (check(mid)) {  // 由于是升序，找最长长度就在右区间查找
      ans = mid;
      L = mid + 1;
    } else {  // 在左区间查找
      R = mid - 1;
    }
  }
  return ans;
}
int main() {
  scanf("%ld%ld", &n, &k);
  long long max_l = 0;           // 最长的长度
  long long sum_l = 0;           // 所有木块的长度之和
  for (int i = 0; i < n; i++) {  // 输入每一根原木的长度
    scanf("%ld", &a[i]);
    max_l = max(max_l, a[i]);  // 所有木块最长长度
    sum_l = sum_l + a[i];      // 所有木块长度之和
  }
  if (sum_l < 1)  // 特殊判断，连1cm长的小段都切不出来，输出0
    printf("0\n");
  else {
    // 采用二分法判断max_w和sum_w之间的重量值哪些满足条件，最后取最小重量
    long long ans = BinaryCheck(1, max_l);  // 调用自定义函数
    printf("%ld\n", ans);
  }
  return 0;
}