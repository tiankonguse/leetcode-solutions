// #include <bits/stdc++.h>

#include "base.h"
using namespace std;


int dp[3003][3003];
string ans(6000, ' ');

typedef long long ll;
class Solution {
 public:
   string largestMerge(const string& word1, const string& word2) {
    int w1 = word1.size();
    int w2 = word2.size();

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < w1; i++) {
      dp[i][w2] = 1;
    }
    for (int j = 0; j < w2; j++) {
      dp[w1][j] = -1;
    }

    for (int i = w1 - 1; i >= 0; i--) {
      for (int j = w2 - 1; j >= 0; j--) {
        if (word1[i] == word2[j]) {
          dp[i][j] = dp[i + 1][j + 1];
        } else if (word1[i] > word2[j]) {
          dp[i][j] = 1;
        } else {
          dp[i][j] = -1;
        }
      }
    }

    int i = 0, j = 0;
    ans.clear();
    while (i < w1 || j < w2) {
      if (dp[i][j] == -1) {
        ans.push_back(word2[j]);
        j++;
      } else {
        ans.push_back(word1[i]);
        i++;
      }
    }

    return ans;
  }
};