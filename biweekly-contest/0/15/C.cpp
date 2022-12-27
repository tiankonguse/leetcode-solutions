// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class CombinationIterator {
  string str;
  vector<int> nums;
  bool endFlag = true;
  int ansFlag = true;
  int n, k;

 public:
  CombinationIterator(string characters, int combinationLength) {
    str = characters;
    n = str.size();

    k = combinationLength;
    for (int i = 0; i < k; i++) {
      nums.push_back(i);
    }
  }

  string next() {
    if (!ansFlag) {
      Add();
    }
    string ans;
    for (auto v : nums) {
      ans.push_back(str[v]);
    }
    ansFlag = false;
    return ans;
  }

  bool Add() {
    int p = k - 1;
    while (p >= 0) {
      nums[p]++;
      if (nums[p] + k - p - 1 < n) {
        for (int i = p + 1; i < k; i++) {
          nums[i] = nums[i - 1] + 1;
        }
        return true;
      }
      p--;
    }
    return endFlag = false;
  }

  bool hasNext() {
    if (!endFlag) {
      return false;
    }
    if (ansFlag) return true;
    return ansFlag = Add();
  }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters,
 * combinationLength); string param_1 = obj->next(); bool param_2 =
 * obj->hasNext();
 */