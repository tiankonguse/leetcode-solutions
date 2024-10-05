// #include <bits/stdc++.h>
/*
题目： 49. 字母异位词分组
地址：https://leetcode.cn/problems/group-anagrams/?envType=study-plan-v2&envId=top-100-liked
考察： hash
问题： 要求将字符串按字母异位词进行分组。
思路： 相同的字母异位词分组放在一起。
时间复杂度： `O(n)`
空间复杂度： `O(n)`
*/

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> ans;
    map<string, int> m;

    for (auto& s : strs) {
      string v = s;
      sort(v.begin(), v.end());
      if (m.count(v) == 0) {
        m[v] = ans.size();
        ans.push_back(vector<string>());
      }
      ans[m[v]].push_back(s);
    }

    return ans;
  }
};