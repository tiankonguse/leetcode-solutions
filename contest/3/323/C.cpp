// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Allocator {
  map<int, int> mem;   // [l, r]
  map<int, int> rmem;  // [r, l]
  unordered_map<int, vector<pair<int, int>>> poll;

 private:
  int Find(int len) {
    for (auto [l, r] : mem) {
      if (r - l + 1 >= len) {
        return l;
      }
    }
    return -1;
  }

  void Erase(int l) {
    int r = mem[l];
    mem.erase(l);
    rmem.erase(r);
  }

  void Free(int l, int r) {
    // after
    if (mem.count(r + 1)) {
      int L = r + 1;
      r = mem[L];
      Erase(L);
    }

    if (rmem.count(l - 1)) {
      int L = rmem[l - 1];
      l = L;
      Erase(L);
    }

    mem[l] = r;
    rmem[r] = l;
  }

 public:
  Allocator(int n) {
    mem[0] = n - 1;
    rmem[n - 1] = 0;
  }

  int allocate(int size, int mID) {
    int l = Find(size);
    if (l == -1) {
      return -1;
    }
    int r = mem[l];
    Erase(l);

    if (r - l + 1 > size) {
      Free(l + size, r);
    }
    poll[mID].push_back({l, l + size - 1});
    return l;
  }

  int free(int mID) {
    int ans = 0;
    for (auto [l, r] : poll[mID]) {
      ans += r - l + 1;
      Free(l, r);
    }
    poll.erase(mID);
    return ans;
  }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */
