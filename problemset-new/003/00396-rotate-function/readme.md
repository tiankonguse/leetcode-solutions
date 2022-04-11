# 396. 旋转函数

给定一个长度为 n 的整数数组 nums 。

假设 arrk 是数组 nums 顺时针旋转 k 个位置后的数组，我们定义 nums 的 旋转函数  F 为：

* `F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]`

返回 F(0), F(1), ..., F(n-1)中的最大值 。

生成的测试用例让答案符合 32 位 整数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-function
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。