// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class FrequencyTracker {
  unordered_map<int, int> h;
  unordered_map<int, int> H;

 public:
  FrequencyTracker() {}

  void add(int v) {
    H[h[v]]--;
    h[v]++;
    H[h[v]]++;
  }

  void deleteOne(int v) {
    if (h[v] == 0) return;
    H[h[v]]--;
    h[v]--;
    H[h[v]]++;
  }

  bool hasFrequency(int v) {
    if (H.count(v) == 0) return false;
    return H[v] > 0;
  }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */