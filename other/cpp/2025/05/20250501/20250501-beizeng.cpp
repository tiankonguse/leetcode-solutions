// 倍增动态规划模版
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// 二进制倍增DP模板
// 用于高效计算多次应用某操作的结果
class BinaryLiftingDP {
 private:
    int n;                   // 数组大小
    int maxLog;              // 所需的最大2的幂
    vector<vector<int>> dp;  // dp[j][i] 表示从位置i开始应用2^j次操作的结果

 public:
    BinaryLiftingDP(const vector<int>& arr) {
        n = arr.size();
        maxLog = log2(n) + 1;

        // 初始化dp表格
        dp.resize(maxLog, vector<int>(n));

        // 基本情况：应用操作2^0 = 1次
        for (int i = 0; i < n; i++) {
            dp[0][i] = arr[i];  // 根据你的操作修改这里
        }

        // 使用二进制倍增填充dp表格
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i < n; i++) {
                int intermediate = dp[j - 1][i];
                dp[j][i] = dp[j - 1][intermediate];  // 先应用操作2^(j-1)次，然后再应用2^(j-1)次
            }
        }
    }

    // 查询从位置pos开始应用操作k次的结果
    int query(int pos, int k) {
        for (int j = 0; j < maxLog && k > 0; j++) {
            if (k & (1 << j)) {
                pos = dp[j][pos];  // 应用操作2^j次
                k -= (1 << j);
            }
        }
        return pos;
    }
};

// 使用示例
void exampleUsage() {
    // 示例数组（可以表示下一个跳转位置）
    vector<int> arr = {2, 3, 1, 4, 0, 5};

    BinaryLiftingDP solver(arr);

    // 查询示例
    cout << "从位置0开始，4次操作后的位置: " << solver.query(0, 4) << endl;
    cout << "从位置2开始，7次操作后的位置: " << solver.query(2, 7) << endl;
}