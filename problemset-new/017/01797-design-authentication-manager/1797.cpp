// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    c.clear();
    c.resize(n + 100, 0);
  }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) { return Query(r) - Query(l - 1); }

  void Add(int x, ll v) {
    while (x <= n) {
      c[x] += v;
      x += Lowbit(x);
    }
  }

 private:
  int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};

const int N = 3000;
TreeArray treeArray;
class AuthenticationManager {
  ll T = 0;
  vector<ll> times;
  unordered_map<string, ll> m;

  void Remove(const string& tokenId) {
    if (m.count(tokenId) == 0) return;
    int t = m[tokenId];
    int offset = lower_bound(times.begin(), times.end(), t) - times.begin();
    treeArray.Add(offset, -1);
  }

 public:
  AuthenticationManager(int timeToLive) {  //
    T = timeToLive;
    times.reserve(N);
    times.push_back(0);
    treeArray.Init(N);
  }

  void generate(const string& tokenId, int currentTime) {  //
    Remove(tokenId);
    ll t = currentTime + T;
    m[tokenId] = t;
    times.push_back(t);
    int offset = lower_bound(times.begin(), times.end(), t) - times.begin();
    treeArray.Add(offset, 1);
    // printf("tokenId=%s currentTime=%d t=%lld offset=%d\n", tokenId.c_str(),
    //        currentTime, t, offset);
  }

  void renew(const string& tokenId, int currentTime) {  //
    if (m.find(tokenId) == m.end()) {
      // printf("tokenId=%s currentTime=%d not find\n", tokenId.c_str(),
      //        currentTime);
      return;  // 不存在，忽略次操作
    }
    if (m[tokenId] <= currentTime) {
      // printf("tokenId=%s currentTime=%d exprie\n", tokenId.c_str(),
      //        currentTime);
      return;  // 已过期，忽略次操作
    }
    generate(tokenId, currentTime);
  }

  int countUnexpiredTokens(int t) {  //
    int offset = upper_bound(times.begin(), times.end(), t) - times.begin();
    int ans = treeArray.Query(offset, N);
    // printf("query t=%d offset=%d ans=%d\n", t, offset,ans);
    return ans;
  }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */