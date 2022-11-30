#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class FreqStack {
  unordered_map<int, int> m;
  vector<vector<int>> sta;
  int maxLev;

 public:
  FreqStack() {
    sta.resize(20000);
    maxLev = 0;
  }

  void push(int val) {
    int num = ++m[val];
    maxLev = max(maxLev, num);
    sta[num].push_back(val);
  }

  int pop() {
    int val = sta[maxLev].back();
    m[val]--;
    sta[maxLev].pop_back();
    if (sta[maxLev].size() == 0) {
      maxLev--;
    }
    return val;
  }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */