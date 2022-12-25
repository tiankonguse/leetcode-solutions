
// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<string> words;
  string target;
  int n;

  int H(int index) { return (index + n * 2) % n; }
  int Solver(int index, int inc) {
    int ans = 0;

    while (words[H(index)] != target) {
      ans++;
      index += inc;
    }
    return ans;
  }

 public:
  int closetTarget(vector<string>& words_, string target_, int startIndex) {
    target.swap(target_);
    words.swap(words_);
    n = words.size();
    bool flag = false;
    for (auto& v : words) {
      if (v == target) {
        flag = true;
        break;
      }
    }
    if (!flag) return -1;

    return min(Solver(startIndex, 1), Solver(startIndex, -1));
  }
};