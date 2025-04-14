
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
  map<char, int> freq;
  string kthPermutation(string& s, long long k) {  // 输入保证非空
    int n = s.size();
    MyPrintf("n = %d, k = %lld s=%s\n", n, k, s.c_str());
    for (auto [ch, count] : freq) {
      MyPrintf("ch = %c, count = %d\n", ch, count);
    };

    string res = "";
    res.reserve(n);
    // 逆序计算总排列数
    ll total = 1;  // 之前已经计算的排列数
    ll num = 0;    // 当前的字符个数
    for (auto it = freq.rbegin(); it != freq.rend(); ++it) {
      if (num == 0) {  // 当前还没有字符
        num = it->second;
        total = 1;
        continue;
      }
      ll count = it->second;
      // 字符总个数： num + count
      // 当前字符的选择数: C(num+count, count) = (num+count)! / (num! * count!)
      // 总答案个数： total * C(num+count, count)
    }
    MyPrintf("res = %s\n", res.c_str());
    return res;
  }

 public:
  string smallestPalindrome(const string& s, int k) {
    freq.clear();
    int n = s.size();
    for (char c : s) {
      freq[c]++;
    }
    char oddVal = 'a';
    for (auto [c, count] : freq) {
      if (count % 2 == 1) {
        oddVal = c;
        freq[c]--;
        break;
      }
    }
    if (freq[oddVal] == 0) freq.erase(oddVal);

    string half;
    half.reserve(n / 2);
    for (auto& [c, count] : freq) {
      int num = count / 2;
      while (num > 0) {
        half.push_back(c);
        num--;
      }
      count = count / 2;
    }
    if (half.empty()) {
      if (k == 1) {
        return s;
      } else {
        return "";  // 不足 k 个
      }
    }
    string halfAns = kthPermutation(half, k);
    if (halfAns.empty()) {
      return "";  // 不足 k 个
    }
    string ans = halfAns;
    if (n % 2 == 1) {
      ans.push_back(oddVal);
    }
    reverse(halfAns.begin(), halfAns.end());
    ans += halfAns;

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif