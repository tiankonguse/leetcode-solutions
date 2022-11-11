#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  unordered_set<char> flag = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
  int Count(const string& s, int l, int r) {
    int num = 0;
    for (int i = l; i < r; i++) {
      if (flag.count(s[i])) {
        num++;
      }
    }
    return num;
  }

 public:
  bool halvesAreAlike(const string& s) {
    int n = s.size();
    return Count(s, 0, n / 2) == Count(s, n / 2, n);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
