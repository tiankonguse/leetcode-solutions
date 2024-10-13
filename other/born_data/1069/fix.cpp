
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

void FixIn() {
  FILE* fin = fopen(TASK ".in", "r");
  double a, b, c;
  ll i = 1;
  while (fscanf(fin, "%lf%lf%lf", &a, &b, &c) != EOF) {
    string filename = TASK;
    filename.append(to_string(i++));
    filename.append(".in");
    FILE* fout = fopen(filename.c_str(), "w");
    a = rand() % 10000;
    b = rand() % 10000;
    c = rand() % 10000;
    fprintf(fout, "%lf %lf %lf\n", a, b, c);
    fclose(fout);
    if (i > 10) break;  // 保护，避免死循环
  }
}

void FixOut() {
  FILE* fin = fopen(TASK ".out", "r");
  char ans[100];
  ll i = 1;
  while (fgets(ans, sizeof(ans), fin) != NULL) {
    string filename = TASK;
    filename.append(to_string(i++));
    filename.append(".out");
    FILE* fout = fopen(filename.c_str(), "w");
    fprintf(fout, "%s\n", ans);
    fclose(fout);
    if (i > 10) break;  // 保护，避免死循环
  }
}

int main() {
  FixIn();
  FixOut();

  return 0;
}
/*
1
0 0 1 1 5
*/