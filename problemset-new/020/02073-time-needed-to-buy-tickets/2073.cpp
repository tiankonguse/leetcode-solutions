// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minMovesToSeat(vector<int>& seats, vector<int>& students) {
    sort(seats.begin(), seats.end());
    sort(students.begin(), students.end());
    int n = seats.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += abs(seats[i] - students[i]);
    }
    return ans;
  }
};