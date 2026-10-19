[Q4. 覆盖目标区间的最少区间](https://leetcode.cn/contest/weekly-contest-524/problems/minimum-interval-selection-to-cover-target-intervals/)

困难

6 分

给你两个二维整数数组 `availableIntervals` 和 `targetIntervals` ，每个数组都表示一系列 **闭区间** 。

从 `availableIntervals` 中选择一个 **子集** ，使得 `targetIntervals` 中任何区间包含的 **每一个实数点** 都属于至少一个被选中的区间。

目标区间之外的点不需要被覆盖。选中的区间可以相互重叠，也可以延伸到目标区间之外。

返回你需要选择的 **最小** 区间数量。如果无法覆盖所有的目标区间，返回 `-1` 。

数组的 **子集** 是指从该数组中选择的一些元素（可能不选择任何元素）组成的集合。

**示例 1：**

**输入：** availableIntervals = \[\[1,4\],\[1,7\],\[3,9\],\[5,10\],\[10,15\]\], targetIntervals = \[\[1,3\],\[2,5\],\[7,8\],\[10,13\],\[11,15\],\[12,13\]\]

**输出：** 3

**解释：**

目标区间覆盖了 `[1, 5]` 、 `[7, 8]` 和 `[10, 15]` 的范围。通过从 `availableIntervals` 中选择 `[1, 4]` 、 `[3, 9]` 和 `[10, 15]` ，可以用三个区间完全覆盖所有的目标区间。

**示例 2：**

**输入：** availableIntervals = \[\[4,6\],\[1,4\],\[2,5\]\], targetIntervals = \[\[3,4\],\[2,5\],\[6,7\]\]

**输出：** -1

**解释：**

无法从 `availableIntervals` 中选择区间来覆盖 `targetIntervals` 中的所有区间。

**示例 3：**

**输入：** availableIntervals = \[\[1,2\],\[3,4\]\], targetIntervals = \[\[1,4\]\]

**输出：** -1

**解释：**

即使选择所有可用的区间，也会使介于 2 和 3 之间的每一个实数点处于未覆盖状态。例如，2.5 属于目标区间，但不属于任何可用的区间。

**提示：**

- `1 <= availableIntervals.length, targetIntervals.length <= 5 * 10<sup>4</sup>`
- `availableIntervals[i].length == targetIntervals[j].length == 2`
- `1 <= availableIntervals[i][0] <= availableIntervals[i][1] <= 10<sup>5</sup>`
- `1 <= targetIntervals[j][0] <= targetIntervals[j][1] <= 10<sup>5</sup>`
