
/*
ID: tiankonguse
TASK: lock
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7813
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// 标准题解
void Solver() {
  int n;
  vector<int> nums;
  scanf("%d", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  sort(nums.begin(), nums.end());

  for (int i = 0; i < n; i++) {
    printf("%d%c", nums[i], i + 1 == n - 1 ? '\n' : ' ');
  }
}

// 生成输入样例输出
void BornData() {
  int n = rand() % 10000;
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    printf("%d%c", rand() % 10000, i + 1 == n - 1 ? '\n' : ' ');
  }
}

#define TASK "sort"  // 输出的文件名签字
int main() {
  int n = 10;
  for (int i = 1; i <= 20; i++) {
    const string taskName = TASK + to_string(i);
    const string inFile = taskName + ".in";
    const string outFile = taskName + ".out";

    // 生成样例数据，输出到文件里
    freopen(inFile.c_str(), "w", stdout);
    BornData();
    fclose(stdout);

    // 把标准输入输出重定向到两个文件里
    freopen(inFile.c_str(), "r", stdin);
    freopen(outFile.c_str(), "w", stdout);
    Solver();  // 运行题解
    fclose(stdin);
    fclose(stdout);
  }
  return 0;
}
/*
1
0 0 1 1 5
*/