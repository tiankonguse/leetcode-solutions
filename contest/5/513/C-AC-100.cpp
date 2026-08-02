
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  vector<int> countTasks(vector<int>& tasks, vector<int>& shifts) {
    int tn = tasks.size();
    int sn = shifts.size();

    vector<ll> taskSuffixSum(tn + 1, 0);  // taskSuffixSum[i] 表示后i个任务的总时间
    vector<ll> taskPrefixSum(tn, 0);      // taskPrefixSum[i] 表示前i个任务的总时间
    for (int i = tn - 1; i >= 0; i--) {
      taskSuffixSum[i] = taskSuffixSum[i + 1] + tasks[i];
    }
    taskPrefixSum[0] = tasks[0];
    for (int i = 1; i < tn; i++) {
      taskPrefixSum[i] = taskPrefixSum[i - 1] + tasks[i];
    }
    vector<int> ans(sn);  // 剩余未完成的任务数
    int preTaskId = 0;
    int preTaskLeftTime = tasks[0];
    for (int i = 0; i < sn; i++) {
      ll shift = shifts[i];
      if (preTaskLeftTime == 0) {
        preTaskId = (preTaskId + 1) % tn;
        preTaskLeftTime = tasks[preTaskId];
      }
      // preTaskId 可能不完整，单独计算
      if (shift < preTaskLeftTime) {
        preTaskLeftTime -= shift;
        ans[i] = tn - preTaskId;
      } else if (shift == preTaskLeftTime) {
        preTaskLeftTime -= shift;
        ans[i] = tn - preTaskId - 1;
      } else {
        shift -= preTaskLeftTime;
        if (shift >= taskSuffixSum[preTaskId + 1]) {
          ans[i] = 0;
          preTaskId = 0;
          preTaskLeftTime = tasks[preTaskId];
        } else {
          ll findSum = taskPrefixSum[preTaskId] + shift;
          preTaskId = upper_bound(taskPrefixSum.begin(), taskPrefixSum.end(), findSum) - taskPrefixSum.begin();
          preTaskLeftTime = taskPrefixSum[preTaskId] - findSum;
          ans[i] = tn - preTaskId;
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& tasks, const vector<int>& shifts, const vector<int>& ans) {
  TEST_SMP2(Solution, countTasks, ans, tasks, shifts);
}

int main() {
  // tasks = [1,1,3,3,8]
  // shifts = [2,9,5,3,9]
  // ans = [4,1,1,0,0]
  Test({1, 1, 3, 3, 8}, {2, 9, 5, 3, 9}, {4, 1, 1, 0, 0});
  return 0;
}

#endif