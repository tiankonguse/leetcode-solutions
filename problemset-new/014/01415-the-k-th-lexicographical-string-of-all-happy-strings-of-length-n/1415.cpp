// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string getHappyString(int n, int k) {
    vector<int> pow2;
    pow2.push_back(1);
    for (int i = 1; i <= 10; i++) {
      pow2.push_back(pow2.back() * 2);
    }

    if (k > 3 * pow2[n - 1]) {
      return "";
    }

    string ans;

    // 第一个字母，三种选择
    int v = (k - 1) / pow2[n - 1];
    ans.push_back('a' + v);
    k -= v * pow2[n - 1];
    n--;

    // 后面的字母，两种选择
    vector<string> dict = {"bc", "ac", "ab"};
    while (n > 0) {
      v = (k - 1) / pow2[n - 1];
      ans.push_back(dict[ans.back() - 'a'][v]);
      k -= v * pow2[n - 1];
      n--;
    }
    return ans;
  }
};