// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> m1, m2;

  void Swap(int i, int j) {
    m1[i]--, m2[i]++;
    m1[j]++, m2[j]--;
  }

  bool Check() {
    int num1 = 0, num2 = 0;
    for (auto v : m1) {
      if (v > 0) num1++;
    }
    for (auto v : m2) {
      if (v > 0) num2++;
    }
    return num1 == num2;
  }

  bool Check(int i, int j) {
    if (m1[i] == 0 || m2[j] == 0) return false;

    Swap(i, j);
    bool ans = Check();
    Swap(j, i);
    return ans;
  }

 public:
  bool isItPossible(string word1, string word2) {
    m1.resize(26, 0);
    m2.resize(26, 0);
    for (auto c : word1) m1[c - 'a']++;
    for (auto c : word2) m2[c - 'a']++;
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        if (Check(i, j)) return true;
      }
    }
    return false;
  }
};