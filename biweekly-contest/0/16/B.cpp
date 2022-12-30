// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
  unordered_set<string> ph;
  unordered_set<string> nh;

  int CalScore(const string& val) {
    int score = 0;
    string tmp;
    for (auto v : val) {
      if (v == ' ') {
        if (ph.count(tmp)) {
          score += 3;
        }
        if (nh.count(tmp)) {
          score -= 1;
        }
        tmp.clear();
      } else {
        tmp.push_back(v);
      }
    }
    if (ph.count(tmp)) {
      score += 3;
    }
    if (nh.count(tmp)) {
      score -= 1;
    }
    return score;
  };

 public:
  vector<int> topStudents(vector<string>& positive_feedback,
                          vector<string>& negative_feedback,
                          vector<string>& report, vector<int>& student_id,
                          int k) {
    for (auto& s : positive_feedback) ph.insert(s);
    for (auto& s : negative_feedback) nh.insert(s);

    int n = report.size();
    vector<pair<int, int>> nums(n);
    for (int i = 0; i < n; i++) {
      nums[i] = {CalScore(report[i]), student_id[i]};
    }
    sort(nums.begin(), nums.end(), [](auto& a, auto& b) {
      if (a.first == b.first) {
        return a.second < b.second;
      } else {
        return a.first > b.first;
      }
    });

    vector<int> ans(k);
    for (int i = 0; i < k; i++) {
      ans[i] = nums[i].second;
    }
    return ans;
  }
};