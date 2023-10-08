// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minProcessingTime(vector<int>& processorTime, vector<int>& tasks) {
    sort(tasks.begin(), tasks.end());
    sort(processorTime.begin(), processorTime.end(),
         [](int a, int b) { return a > b; });

    int ans = 0;
    int n = processorTime.size();
    for (int i = 0; i < n * 4; i++) {
      ans = max(ans, tasks[i] + processorTime[i / 4]);
    }
    return ans;
  }
};