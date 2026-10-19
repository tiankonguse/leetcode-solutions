
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
  // R → B → W → R → B → W
  unordered_map<char, char> nextColor = {{'R', 'B'}, {'B', 'W'}, {'W', 'R'}};
  char PreColor(char c) {
    return nextColor[nextColor[c]];  //
  }
  bool DfsCheck(int u, int pre) {
    char preColor = PreColor(colors[u]);
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
    int root = -1;
    for (int i = 0; i < n; i++) {
      if (degree[i] == 1) {
        int u = i;
        int v = g[u][0];
        if (nextColor[colors[u]] == colors[v]) {
          root = u;
          break;
        }
      } else if (degree[i] == 2) {
        int u = i;
        int v0 = g[u][0];
        int v1 = g[u][1];
        if (nextColor[colors[u]] == colors[v0] && colors[v0] == colors[v1]) {
          root = u;
          break;
        }
      }
    }
    if (root != -1 && DfsCheck(root, -1)) {
      return root;
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