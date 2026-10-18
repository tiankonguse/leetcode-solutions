
class Solution {
  vector<vector<int>> g;
  int n;
  vector<int> degree;
  string colors;

  bool DfsCheck(int u, int pre) {
    char preColor = ' ';
    if (pre == -1) {
      if (degree[u] == 3) return false;  // 度为 3 的节点不可能是根
      if (degree[u] == 2 && colors[g[u][0]] != colors[g[u][1]]) {
        return false;  // 两个儿子节点颜色不同，不可能是根
      }
      if (colors[u] == 'R') {
        preColor = 'W';
      } else if (colors[u] == 'W') {
        preColor = 'B';
      } else {
        preColor = 'R';
      }
    } else {
      preColor = colors[pre];
    }
    for (auto v : g[u]) {
      if (v == pre) continue;
      if (colors[v] == preColor) return false;
      if (!DfsCheck(v, u)) return false;
    }
    return true;
  }

 public:
  int findColoredRoot(vector<vector<int>>& edges, string colors_) {
    colors.swap(colors_);
    n = colors.size();
    g.assign(n, vector<int>()); 
    degree.assign(n, 0);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
      degree[u]++;
      degree[v]++;
      if (colors[v] == colors[u]) {
        return -1;  // 相邻节点颜色必须不同
      }
    }
    int maxDeg = 0, degIndex3 = -1;
    for (int i = 0; i < n; i++) {
      maxDeg = max(maxDeg, degree[i]);
      if (degree[i] == 3) {
        degIndex3 = i;
      }
    }

    if (maxDeg == 1) {
      // n = 2，颜色不同时任意节点都可以是根
      if (colors[0] != colors[1]) {
        for (int i = 0; i < 2; i++) {
          if (DfsCheck(i, -1)) {
            return i;
          }
        }
      }
    } else if (maxDeg == 2) {
      // 是一个链
      int cnt = 0, root = -1;
      vector<int> leafs;
      for (int i = 0; i < n; i++) {
        if (g[i].size() == 2) {
          if (colors[g[i][0]] == colors[g[i][1]]) {
            cnt++;  // 左右同色，i 必须是根
            root = i;
          }
        } else {
          leafs.push_back(i);
        }
      }
      if (cnt == 0) {
        for (auto root : leafs) {
          if (DfsCheck(root, -1)) {
            return root;
          }
        }
      } else if (cnt == 1) {
        if (DfsCheck(root, -1)) {
          return root;
        }
      }
    } else {
      // 度为 3 的树
      int faIndex = -1;
      for (int i = 0; i < 3; i++) {
        if (colors[g[degIndex3][(i + 1) % 3]] == colors[g[degIndex3][(i + 2) % 3]]) {
          faIndex = i;  // 颜色相同的两个节点是儿子，剩余的是父亲
        }
      }
      if (faIndex == -1) return -1;
      int fa = g[degIndex3][faIndex];
      int child = degIndex3;
      int root = -1;
      while (1) {
        if (degree[fa] == 3) {
          int fafa = -1, otherChild = -1;
          for (int i = 0; i < 3; i++) {
            if (g[fa][i] != child) {
              if (colors[g[fa][i]] != colors[child]) {
                fafa = g[fa][i];
              } else {
                otherChild = g[fa][i];
              }
            }
          }
          if (fafa == -1 || otherChild == -1) {
            return -1;
          }
          child = fa;
          fa = fafa;
        } else if (degree[fa] == 2) {
          if (colors[g[fa][0]] == colors[g[fa][1]]) {
            root = fa;  // 左右同色，只能作为根
            break;
          } else {
            // 不能作为根
            int fafa = -1;
            for (int i = 0; i < 2; i++) {
              if (g[fa][i] != child) {
                fafa = g[fa][i];
              }
            }
            child = fa;
            fa = fafa;
          }
        } else {
          root = fa;  // 度为 1，只能作为根
          break;
        }
      }
      if (DfsCheck(root, -1)) {
        return root;
      }
    }
    return -1;
  }
};