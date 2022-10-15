class Solution {
 public:
  /*
  . 只取0
  / 0为左上1为右下
  \ 0为右上1为左下
  */
  int encode(int r, int c, int b) { return (r * C + c) * 2 + b; }
  tuple<int, int, int> decode(int w) {
    return {(w / 2) / C, (w / 2) % C, w & 1};
  }
  void dfs(int r, int c, int b, int w, int lim) {
    if (vis[w]) return;
    ans += (r > lim) * ((shape[r][c] == '.') + 1);
    vis[w] = true;
    if (r - 1 >= lim) {  // 尝试向上
      bool ok = (b == 0);
      int up_b = shape[r - 1][c] == '.' ? 0 : 1;
      int up = encode(r - 1, c, up_b);
      if (ok && !vis[up]) {
        dfs(r - 1, c, up_b, up, lim);
      }
    }
    if (r + 1 < R) {  // 尝试向下
      bool ok = (shape[r][c] == '.' || b == 1);
      int down = encode(r + 1, c, 0);
      if (ok && !vis[down]) {
        dfs(r + 1, c, 0, down, lim);
      }
    }
    if (c - 1 >= 0) {  // 尝试向左
      bool ok = (shape[r][c] == '.' || (shape[r][c] == 'r' && b == 0) ||
                 (shape[r][c] == 'l' && b == 1));
      int left_b = shape[r][c - 1] == 'r' ? 1 : 0;
      int left = encode(r, c - 1, left_b);
      if (ok && !vis[left]) {
        dfs(r, c - 1, left_b, left, lim);
      }
    }
    if (c + 1 < C) {  // 尝试向右
      bool ok = (shape[r][c] == '.' || (shape[r][c] == 'r' && b == 1) ||
                 (shape[r][c] == 'l' && b == 0));
      int right_b = shape[r][c + 1] == 'l' ? 1 : 0;
      int right = encode(r, c + 1, right_b);
      if (ok && !vis[right]) {
        dfs(r, c + 1, right_b, right, lim);
      }
    }
  }
  int reservoir(vector<string>& raw) {
    // 预处理，用点包围一圈
    shape.clear();
    R = raw.size() + 2;
    C = raw[0].size() + 2;
    shape.emplace_back(C, '.');
    for (auto& s : raw) shape.emplace_back('.' + s + '.');
    shape.emplace_back(C, '.');
    // init
    vis = vector<bool>(encode(R - 1, C - 1, 1) + 1, false);
    // 最后一行置为空气
    for (int c = 0; c < C; c++) {
      vis[encode(R - 1, c, 0)] = true;
    }
    // 处理每行
    ans = 0;
    for (int r = R - 2; r >= 0; r--) {
      // 从上一行的空气蔓延到当前层再dfs
      for (int c = 0; c < C; c++) {
        if (!vis[encode(r + 1, c, 0)]) continue;
        if (shape[r][c] == '.')
          dfs(r, c, 0, encode(r, c, 0), r);  // 只有0
        else
          dfs(r, c, 1, encode(r, c, 1), r);  // 1在下
      }
    }
    return ans;
  }
  int R;
  int C;
  int ans = 0;
  vector<string> shape;
  vector<bool> vis;
};