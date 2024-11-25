// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

/*
问题: n 个坐标的最大曼哈顿距离

假设有两点 `(x0,y0)` 和 `(x1,y1)`，曼哈顿距离为 `abs(x0-x1)+abs(y0-y1)`。  

如果把绝对值展开，则分为四种情况，蔓哈顿距离为四种情况的最大值。  

```
+(x0-x1) + (y0-y1)
+(x0-x1) - (y0-y1)
-(x0-x1) - (y0-y1)
-(x0-x1) - (y0-y1)
```

分为两个坐标的关系，即如下  

```
(x0+y0) - (x1+y1)
(x0-y0) - (x1-y1)
(-x0-y0) - (-x1-y1)
(-x0+y0) - (-x0+y1)
```

可以发现，四种情况两个坐标中 X 与 Y 的符号是相同的。  

n 个坐标时，有 4N 个这样的公式，根据符号可以分为四组。  
每一组的最大值显然是组内的最大值减去组内的最小值。  

故可以对组内公式的值排序，从而得到每组内的最大值。  
四组内的最大值中的最大值就是 n 个坐标的最大曼哈顿距离。  


复杂度：`n log(n)`  
*/


typedef long long ll;
const int dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int MaxDistance(vector<vector<int>> &points) {
  int n = points.size();
  vector<vector<int>> nums(4, vector<int>(n));
  for (int i = 0; i < n; i++) {
    auto x = points[i][0], y = points[i][1];
    for (int k = 0; k < 4; k++) {
      nums[k][i] = x * dirs[k][0] + y * dirs[k][1];
    }
  }

  for (int k = 0; k < 4; k++) {
    sort(nums[k].begin(), nums[k].end());
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int tmp = 0;
    for (int k = 0; k < 4; k++) {
      tmp = max(tmp, nums[k].back() - nums[k].front());
    }
    ans = max(ans, tmp);
  }
  return ans;
}