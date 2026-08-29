#include <bits/stdc++.h>
using namespace std;

// int ans = 0;
bool col[9];
bool dia1[20], dia2[20];

vector<vector<int>> ans;
vector<int> path;
void dfs(int row) {
  if (row == 8) {
    // ans++;
    ans.push_back(path);
    return;
  }
  for (int c = 1; c <= 8; c++) {
    int d1 = 8 + c - row;
    int d2 = 17 - c - row;
    if (col[c] && dia1[d1] && dia2[d2]) {
      col[c] = false;
      dia1[d1] = false;
      dia2[d2] = false;
      path.push_back(c);
      dfs(row + 1);
      path.pop_back();
      col[c] = true;
      dia1[d1] = true;
      dia2[d2] = true;
    }
  }
}
int main() {
  int a;
  scanf("%d", &a);
  fill(col, col + 9, true);
  fill(dia1, dia1 + 20, true);
  fill(dia2, dia2 + 20, true);
  path.reserve(100);
  dfs(0);
  for(int i=0;i<3;i++){
    for(int j=0;j<8;j++){
        printf("%d%c", ans[i][j], j == 7 ? '\n' : ' ');
    }
  }
  printf("%d\n", ans.size());
  return 0;
}