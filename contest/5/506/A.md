给你一个正整数 `n` 。

令 `digitSum` 表示 `n` 的各位数字之和，令 `squareSum` 表示 `n` 的各位数字平方之和。

如果一个整数满足 `squareSum - digitSum >= 50` ，则称它是 **好整数** 。

如果 `n` 是好整数，返回 `true` ；否则，返回 `false` 。

**示例 1：**

**输入：** n = 1000

**输出：** false

**解释：**

- 1000 的数字为 1、0、0 和 0。
- `digitSum` 为 `1 + 0 + 0 + 0 = 1` 。
- `squareSum` 为 `1<sup>2</sup> + 0<sup>2</sup> + 0<sup>2</sup> + 0<sup>2</sup> = 1` 。
- `squareSum - digitSum` 为 `1 - 1 = 0` 。由于 0 小于 50，因此输出 `false` 。

**示例 2：**

**输入：** n = 19

**输出：** true

**解释：**

- 19 的数字为 1 和 9。
- `digitSum` 为 `1 + 9 = 10` 。
- `squareSum` 为 `1<sup>2</sup> + 9<sup>2</sup> = 1 + 81 = 82` 。
- `squareSum - digitSum` 为 `82 - 10 = 72` 。由于 72 大于等于 50，因此输出 `true` 。

**提示：**

- `1 <= n <= 10<sup>9</sup>`

