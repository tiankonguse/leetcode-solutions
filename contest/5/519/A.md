给你一个整数 `n` 、一个大小为 `n x n` 的二维整数数组 `grid` ，以及两个长度均为 `n` 的整数数组 `rowShift` 和 `colShift` ，其中：

- `rowShift[i]` 表示将 `grid` 的第 `i` 行向左 **循环移位** 的位数。
- `colShift[j]` 表示将 `grid` 的第 `j` 列向上 **循环移位** 的位数。

首先按照 `rowShift` 对每一行进行循环移位，然后按照 `colShift` 对每一列进行循环移位。

返回完成所有移位操作后的网格。

将第 `i` 行向左 **循环移位** `k` 位时，只移动该行。原本位于第 `j` 列的元素会移动到第 `(j - k + n) % n` 列，其余各行保持不变。

将第 `j` 列向上 **循环移位** `k` 位时，只移动该列。原本位于第 `i` 行的元素会移动到第 `(i - k + n) % n` 行，其余各列保持不变。

**示例 1：**

**输入：** n = 2, `grid` = \[\[1,2\],\[3,4\]\], rowShift = \[1,0\], colShift = \[0,1\]

**输出：** \[\[2,4\],\[3,1\]\]

**解释：**

`grid` 的变化过程如下：

![](https://assets.leetcode.com/uploads/2026/08/18/4743-1.png)

**示例 2：**

**输入：** n = 3, `grid` = \[\[1,2,3\],\[4,5,6\],\[7,8,9\]\], rowShift = \[1,2,0\], colShift = \[2,2,1\]

**输出：** \[\[7,8,5\],\[2,3,9\],\[6,4,1\]\]

**解释：**

`grid` 的变化过程如下：

![](https://assets.leetcode.com/uploads/2026/08/18/4743-2.png)

**提示：**

- `1 <= n == grid.length == grid[i].length <= 10`
- `1 <= grid[i][j] <= 100`
- `rowShift.length == colShift.length == n`
- `0 <= rowShift[i], colShift[i] < n`
