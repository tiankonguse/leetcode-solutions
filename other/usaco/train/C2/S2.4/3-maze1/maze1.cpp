/*
ID: tiankonguse
TASK: maze1
LANG: C++

warning: this program uses gets(), which is unsafe.

gets is unsafe because you give it a buffer, but you don't tell it how big the buffer is. 
The input may write past the end of the buffer, blowing up your program fairly spectacularly. 
Using fgets instead is a bit better because you tell it how big the buffer is, like this:

const int bufsize = 4096;
char buffer[bufsize];
fgets(buffer, bufsize, stdin);
https://stackoverflow.com/questions/2973985/why-gets-is-not-working
*/
#define TASK "maze1"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

char str[250][250];
int flag[250][250];
queue<pair<int, int>> que;

int ans = 1;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void Add(int x, int y, int step) {
  if (flag[x][y] == 0) {
    flag[x][y] = step;
    ans = max(ans, step);
    que.push({x, y});
  }
}

void Solver() {  //
  int n, m;
  scanf("%d%d", &m, &n);
  getchar();  // skip last \n
  for (int i = 0; i < 2 * n + 1; i++) {
    fgets(str[i], sizeof(str[i]), stdin);
  }

  memset(flag, 0, sizeof(flag));
  for (int j = 1; j < 2 * m + 1; j += 2) {
    if (str[0][j] == ' ') {
      Add(1, j, 1);
      str[0][j] = '#';
    }
    if (str[2 * n][j] == ' ') {
      Add(2 * n - 1, j, 1);
      str[2 * n][j] = '#';
    }
  }
  for (int i = 1; i < 2 * n + 1; i += 2) {
    if (str[i][0] == ' ') {
      Add(i, 1, 1);
      str[i][0] = '#';
    }
    if (str[i][2 * m] == ' ') {
      Add(i, 2 * m - 1, 1);
      str[i][2 * m] = '#';
    }
  }

  while (!que.empty()) {
    auto [x, y] = que.front();
    const int nextStep = flag[x][y] + 1;
    que.pop();
    for (int k = 0; k < 4; k++) {
      int X = x + dir[k][0];
      int Y = y + dir[k][1];
      if (str[X][Y] == ' ') {
        str[X][Y] = '#';
        X += dir[k][0];
        Y += dir[k][1];
        Add(X, Y, nextStep);
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/