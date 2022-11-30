#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class FreqStack {
  unordered_map<int, int> m;
  vector<vector<int>> sta;

 public:
  FreqStack() {
    sta.reserve(20000);
    sta.resize(1);
  }

  void push(int val) {
    m[val]++;
    int num = m[val];
    if (num == sta.size()) {
      sta.resize(num + 1);
    }
    sta[num].push_back(val);
  }

  int pop() {
    int val = sta.back().back();
    sta.back().pop_back();
    if (sta.back().size() == 0) {
      sta.pop_back();
    }

    m[val]--;
    if (m[val] == 0) {
      m.erase(val);
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