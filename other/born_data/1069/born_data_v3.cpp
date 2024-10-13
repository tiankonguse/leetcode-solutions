
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
  double a, b, c, s, area;  // 注意数据类型double

  scanf("%lf%lf%lf", &a, &b, &c);
  if (a + b > c && a + c > b && b + c > a) {
    s = (a + b + c) * 1.0 / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    printf("%.2f\n", area);
  } else {
    printf("error input\n");
  }
}

// 生成输入样例输出
void BornData() {
  double a = rand() % 10;
  double b = rand() % 10;
  double c = rand() % 10;
  printf("%lf %lf %lf\n", a, b, c);
}

#define TASK "test"  // 输出的文件名签字
int main() {
  int n = 10;
  for (int i = 1; i <= 10; i++) {
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