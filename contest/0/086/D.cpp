// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 启发式极小化极大算法
class Solution {
  vector<vector<int>> similar;
  vector<bool> isValid;
  int n;

  // get similarity bettween words:
  void getSim(vector<string>& wordlist) {
    for (int i = 0; i < n; ++i) {
      similar[i][i] = 6;
      for (int j = i + 1; j < n; ++j) {
        int cnt = 0;
        for (int k = 0; k < 6; ++k) cnt += (wordlist[i][k] == wordlist[j][k]);
        similar[i][j] = cnt;
        similar[j][i] = cnt;
      }
    }
  }

  // find the next search point;
  int findNext() {
    int next = -1, maxVal = INT_MAX;
    for (int i = 0; i < n; ++i) {
      if (!isValid[i]) continue;
      vector<int> counter(6, 0);
      for (int j = 0; j < n; ++j) {
        if (j == i || !isValid[j]) continue;
        ++counter[similar[i][j]];
      }
      int currMax = *max_element(counter.begin(), counter.end());
      if (currMax < maxVal) {
        maxVal = currMax;
        next = i;
      }
    }
    return next;
  }

 public:
  void findSecretWord(vector<string>& wordlist, Master& master) {
    n = wordlist.size();
    similar.resize(n, vector<int>(n, 0));
    isValid.resize(n, true);
    getSim(wordlist);

    while (true) {
      int next = findNext();
      int point = master.guess(wordlist[next]);
      if (point == 6) return;
      for (int i = 0; i < n; ++i) {
        if (similar[next][i] != point) isValid[i] = false;
      }
    }
  }
};

// 作者：老杜振熙
// 链接：https://leetcode.cn/problems/guess-the-word/solutions/1/cshi-xian-by-du-uuuuuu-3/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
