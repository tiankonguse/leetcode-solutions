/*
ID: tiankonguse
TASK: ttwo
LANG: C++
*/
#define TASK "ttwo"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
char str[12][12];
const int n = 10;
int cx, cy, cd;
int fx, fy, fd;
int flag[4][12][12][4][12][12];
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void Next(int& d, int& x, int& y) {
  int X = x + dir[d][0];
  int Y = y + dir[d][1];
  if (str[X][Y] != '.') {
    d = (d + 1) % 4;
  } else {
    x = X;
    y = Y;
  }
}

void Solver() {  //
  memset(str, '*', sizeof(str));
  for (int i = 1; i <= n; i++) {
    scanf("%s", &str[i][1]);
    str[i][n + 1] = '*';
    for (int j = 1; j <= n; j++) {
      if (str[i][j] == 'C') {
        cx = i;
        cy = j;
        cd = 0;
        str[i][j] = '.';
      } else if (str[i][j] == 'F') {
        fx = i;
        fy = j;
        fd = 0;
        str[i][j] = '.';
      }
    }
  }

  memset(flag, -1, sizeof(flag));
  flag[cd][cx][cy][fd][fx][fy] = 0;
//   printf("[%d,%d,%d] [%d,%d,%d]\n", cd, cx, cy, fd, fx, fy);
  while (true) {
    const int step = flag[cd][cx][cy][fd][fx][fy] + 1;
    Next(cd, cx, cy);
    Next(fd, fx, fy);
    // printf("[%d,%d,%d] [%d,%d,%d]\n", cd, cx, cy, fd, fx, fy);
    if (cx == fx && cy == fy) {
      printf("%d\n", step);
      break;
    }
    if (flag[cd][cx][cy][fd][fx][fy] != -1) {
      printf("0\n");
      break;
    }
    flag[cd][cx][cy][fd][fx][fy] = step;
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/