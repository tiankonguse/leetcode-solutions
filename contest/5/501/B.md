给你一个字符串数组 `chunks` 。按顺序将这些字符串拼接起来，形成一个字符串 `s` 。

另给定一个字符串数组 `queries` 。

**单词** 定义为 `s` 的一个 **子串** ，并满足：

- 由小写英文字母（ `'a'` 到 `'z'` ）组成；
- 可以包含连字符（ `'-'` ），但仅当每个连字符两侧都被小写英文字母包围时才允许；
- 它不是某个同样满足上述条件更长子串的一部分。

任何不是小写英文字母或合法连字符的字符都会作为分隔符。

返回一个整数数组 `ans` ，其中 `ans[i]` 表示 `queries[i]` 作为单词在 `s` 中出现的次数。

**子串** 是字符串中一个连续的 **非空** 字符序列。

**示例 1：**

**输入：** chunks = \["hello wor","ld hello"\], queries = \["hello","world","wor"\]

**输出：** \[2,1,0\]

**解释：**

- 将 `chunks` 中的所有字符串拼接后，得到 `s = "hello world hello"` 。
- `s` 中的有效单词为 `"hello"` （出现两次）和 `"world"` （出现一次）。
- 因此， `ans = [2, 1, 0]` 。

**示例 2：**

**输入：** chunks = \["a--b a-","-c"\], queries = \["a","b","c"\]

**输出：** \[2,1,1\]

**解释：**

- 将 `chunks` 中的所有字符串拼接后，得到 `s = "a--b a--c"` 。
- `s` 中的有效单词为 `"a"` （出现两次）、 `"b"` （出现一次）和 `"c"` （出现一次）。
- 因此， `ans = [2, 1, 1]` 。

**示例 3：**

**输入：** chunks = \["hello"\], queries = \["hello","ell"\]

**输出：** \[1,0\]

**解释：**

- `s` 中唯一的有效单词是 `"hello"` ，出现一次。
- 因此， `ans = [1, 0]` 。

**提示：**

- `1 <= chunks.length <= 10<sup>5</sup>`
- `1 <= chunks[i].length <= 10<sup>5</sup>`
- `chunks[i]` 可以由小写英文字母、空格和连字符组成。
- 所有 `chunks` 中字符串的总长度不超过 `10<sup>5</sup>`
- `1 <= queries.length <= 10<sup>5</sup>`
- `1 <= queries[i].length <= 10<sup>5</sup>`
- `queries[i]` 是一个有效单词
- 所有 `queries` 中字符串的总长度不超过 `10<sup>5</sup>`


class Solution {

public:

vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {

}

};
