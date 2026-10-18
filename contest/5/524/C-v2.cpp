
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
// 要求1：从根节点到叶子节点，连续三个节点的颜色不同
// 要求2：从根节点开始，三个颜色的顺序满足 R->W->B->W->B，其中根节点可以是任意颜色
// 思路：分情况讨论
// 度数最多为1, 则只能是两个节点
// 度数最多为2，则是一个链，树根要么是第一个节点，要么是第二个节点
// 度数最多为3，答案唯一，根据两个儿子节点的颜色判断边的方向，然后从下往上推导出根节点
// 根确定后，按题意 dfs 检查是否符合要求
class Solution {
  vector<vector<int>> g;
  int n;
  vector<int> degree;
  string colors;

  bool DfsCheck(int u, int pre) {
    char preColor = ' ';
    if (pre == -1) {
      if (degree[u] == 3) return false;  // 三个节点不可能是根
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
      // 保证相邻的颜色不同
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
    g.resize(n);
    degree.resize(n, 0);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
      degree[u]++;
      degree[v]++;
      // 剪枝
      if (colors[v] == colors[u]) return -1;
    }
    int maxDeg = 0, degIndex3 = -1;
    for (int i = 0; i < n; i++) {
      maxDeg = max(maxDeg, degree[i]);
      if (degree[i] == 3) {
        degIndex3 = i;
      }
    }

    if (maxDeg == 1) {
      // n = 2
      if (colors[0] != colors[1]) {
        // 任意一个节点都可以是根
        for (int i = 0; i < 2; i++) {
          if (DfsCheck(i, -1)) {
            return i;
          }
        }
        return -1;
      } else {
        return -1;
      }
    } else if (maxDeg == 2) {
      // 是一个链
      int cnt = 0, root = -1;
      vector<int> leafs;
      for (int i = 0; i < n; i++) {
        if (g[i].size() == 2) {
          if (colors[g[i][0]] == colors[g[i][1]]) {
            // 左右相等，i 必须是根
            cnt++;
            root = i;
          }
        } else {
          leafs.push_back(i);
        }
      }
      MyPrintf("cnt=%d root=%d\n", cnt, root);
      if (cnt == 0) {
        for (auto root : leafs) {
          if (DfsCheck(root, -1)) {
            return root;
          }
        }
        return -1;
      } else if (cnt == 1) {
        if (DfsCheck(root, -1)) {
          return root;
        } else {
          return -1;
        }
      } else {
        return -1;
      }
    } else {
      // 度为 3 ，是一个树
      if (g[degIndex3][0] == g[degIndex3][1] && g[degIndex3][0] == g[degIndex3][2]) {
        return -1;
      }
      int faIndex = -1;
      // 值相同的两个节点是儿子，剩余的是父亲
      for (int i = 0; i < 3; i++) {
        if (colors[g[degIndex3][(i + 1) % 3]] == colors[g[degIndex3][(i + 2) % 3]]) {
          faIndex = i;
        }
      }
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
            // 只能作为根
            root = fa;
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
          // 度为1，只能作为根
          root = fa;
          break;
        }
      }
      if (DfsCheck(root, -1)) {
        return root;
      } else {
        return -1;
      }
    }
    return -1;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif