// 状态压缩动态规划模板
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

// 状态压缩DP示例：旅行商问题(TSP)
class StateCompressionDP {
 private:
  int n;                      // 节点数量
  vector<vector<int>> dp;     // dp[state][i] 表示当前访问节点集合为state，结束于节点i的最小成本
  vector<vector<int>> graph;  // 表示图的邻接矩阵

 public:
  StateCompressionDP(const vector<vector<int>>& costMatrix) {
    n = costMatrix.size();
    graph = costMatrix;

    // 初始化DP数组
    // (1 << n)表示总共有2^n个状态
    dp.resize(1 << n, vector<int>(n, INT_MAX));

    // 基础情况：只访问起点0
    dp[1][0] = 0;  // 状态1表示只访问了节点0，成本为0
  }

  // 解决旅行商问题
  int solveTSP() {
    // 遍历所有可能的状态
    for (int state = 1; state < (1 << n); state++) {
      // 如果状态不包含起点0，则跳过
      if (!(state & 1)) continue;

      // 对于当前状态中的每个节点
      for (int i = 0; i < n; i++) {
        // 如果节点i不在当前状态中，则跳过
        if (!(state & (1 << i))) continue;

        // 计算前一个状态（不包含节点i）
        int prevState = state & ~(1 << i);

        // 如果是起点且状态只有起点，dp值已初始化为0
        if (i == 0 && prevState == 0) continue;

        // 对于前一个状态中的每个节点j
        for (int j = 0; j < n; j++) {
          // 如果节点j在前一个状态中
          if (prevState & (1 << j)) {
            // 尝试从j到i的转移
            if (dp[prevState][j] != INT_MAX && graph[j][i] != INT_MAX) {
              dp[state][i] = min(dp[state][i], dp[prevState][j] + graph[j][i]);
            }
          }
        }
      }
    }

    // 所有节点都被访问，且最后在节点i，还需要从i返回到起点0
    int finalState = (1 << n) - 1;  // 全1状态，表示所有节点都已访问
    int result = INT_MAX;

    for (int i = 0; i < n; i++) {
      if (dp[finalState][i] != INT_MAX && graph[i][0] != INT_MAX) {
        result = min(result, dp[finalState][i] + graph[i][0]);
      }
    }

    return result;
  }

  // 打印状态
  static void printState(int state, int n) {
    cout << "State: " << bitset<16>(state) << " (";
    for (int i = 0; i < n; i++) {
      if (state & (1 << i)) {
        cout << i << " ";
      }
    }
    cout << ")" << endl;
  }
};

// 使用示例
void exampleUsage() {
  // 示例：4个城市的距离矩阵
  vector<vector<int>> distances = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};

  StateCompressionDP solver(distances);
  int minDistance = solver.solveTSP();

  cout << "最短环游路径长度: " << minDistance << endl;
}