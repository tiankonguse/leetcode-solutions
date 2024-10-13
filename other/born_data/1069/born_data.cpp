
/*
ID: tiankonguse
TASK: lock
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7813
*/
#define TASK "test"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define BORN_CODE 1

#define MyScanf(...)            \
  do {                          \
    if (BORN_CODE) {            \
      fscanf(fin, __VA_ARGS__); \
    } else {                    \
      scanf(__VA_ARGS__);       \
    }                           \
  } while (0)

#define MyPrintf(...)             \
  do {                            \
    if (BORN_CODE) {              \
      fprintf(fout, __VA_ARGS__); \
    } else {                      \
      printf(__VA_ARGS__);        \
    }                             \
  } while (0)

// 正确答案的输入 scanf 使用 MyPrintf 代替， 输出 printf 使用 MyPrintf 代替
void Solver(FILE* fin, FILE* fout) {
  double a, b, c, s, area;  // 注意数据类型double

  MyScanf("%lf%lf%lf", &a, &b, &c);
  if (a + b > c && a + c > b && b + c > a) {
    s = (a + b + c) * 1.0 / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    MyPrintf("%.2f\n", area);
  } else {
    MyPrintf("error input\n");
  }
}

void BornData(FILE* fdata) {
  double a = rand() % 10000;
  double b = rand() % 10000;
  double c = rand() % 10000;
  fprintf(fdata, "%lf %lf %lf\n", a, b, c);
}

void Born() {
  FILE* fdata;
  FILE* fin;
  FILE* fout;

  int n = 10;
  for (int i = 1; i <= 10; i++) {
    const string taskName = TASK + to_string(i);
    const string inFile = taskName + ".in";
    const string outFile = taskName + ".out";

    // 生成的数据输出到文件
    fdata = fopen(inFile.c_str(), "w");
    BornData(fdata);
    fclose(fdata);

    fin = fopen(inFile.c_str(), "r");
    fout = fopen(outFile.c_str(), "w");
    Solver(fin, fout);  // 运行题解，
    fclose(fin);
    fclose(fout);
  }
}

int main() {
  Born();
  return 0;
}
/*
1
0 0 1 1 5
*/