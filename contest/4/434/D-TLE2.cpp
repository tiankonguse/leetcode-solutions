
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> supersequences(vector<string>& words) {
    set<char> twoVals;
    map<char, int> h;
    for (auto& w : words) {
      char a = w[0], b = w[1];
      h[a] = h[b] = 0;
      if (a == b) {
        twoVals.insert(a);
      }
    }
    const int charNum = h.size();
    for (auto c : twoVals) {
      h.erase(c);
    }
    const int m = h.size();  // 字符个数
    string s;
    for (auto& [k, v] : h) {
      v = s.size();
      // printf("c=%c index=%d\n", k, v);
      s.push_back(k);
    }

    vector<set<int>> g;
    vector<set<int>> rg;
    auto Check = [&](int mask) -> bool {
      // mask 都是1，判断 words 是否成立
      rg.clear();
      rg.resize(m);
      g.clear();
      g.resize(m);
      for (auto& w : words) {
        const char a = w[0], b = w[1];
        if (twoVals.count(a) || twoVals.count(b)) continue;
        int ai = h[a], bi = h[b];
        if ((mask & (1 << ai)) == 0) continue;
        if ((mask & (1 << bi)) == 0) continue;
        // printf("add %c[%d]->%c[%d]\n", a, ai, b, bi);
        rg[bi].insert(ai);
        g[ai].insert(bi);
      }
      vector<int> zeroInDeg;
      for (int i = 0; i < m; i++) {
        if ((mask & (1 << i)) == 0) continue;  // mask 没有选择 i
        if (rg[i].empty()) {
          zeroInDeg.push_back(i);
        }
      }
      while (!zeroInDeg.empty()) {
        int ai = zeroInDeg.back();
        zeroInDeg.pop_back();
        for (auto bi : g[ai]) {
          rg[bi].erase(ai);
          if (rg[bi].empty()) {
            zeroInDeg.push_back(bi);
          }
        }
        g[ai].clear();
      }
      for (auto& a : rg) {
        if (!a.empty()) return false;
      }
      return true;
    };

    int nowAns = charNum * 2;
    vector<int> ansList(1, 0);
    if (m > 0) {
      const int M = 1 << m;
      vector<int> flag(M, 0);
      queue<int> que;  // bfs 枚举所有自己
      que.push(M - 1);
      flag[M - 1] = 1;

      while (!que.empty()) {
        const int mask = que.front();
        que.pop();

        const int oneNum = __builtin_popcount(mask);
        const int twoNum = charNum - oneNum;
        const int tmpAns = twoNum * 2 + oneNum;
        // printf("mask=%d oneNum=%d twoNum=%d tmpAns=%d\n", mask, oneNum, twoNum, tmpAns);
        if (tmpAns > nowAns) continue;  // 答案更大，说明后面的都会更大

        const bool ok = Check(mask);
        // printf("check=%d\n", ok);
        if (ok) {
          if (tmpAns < nowAns) {
            ansList.clear();
          }
          ansList.push_back(mask);
          nowAns = tmpAns;
        } else {
          // 当前没有答案，加入所有的儿子
          for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) {
              const int child = mask ^ (1 << i);
              if (flag[child] == 0) {
                que.push(child);
                flag[child] = 1;
              }
            }
          }
        }
      }
    }

    vector<vector<int>> ans;
    ans.reserve(ansList.size());
    for (auto mask : ansList) {
      // printf("mask=%d\n", mask);
      vector<int> oneAns(26, 0);
      for (auto c : twoVals) {
        oneAns[c - 'a'] = 2;
      }
      for (int i = 0; i < m; i++) {
        if (mask & (1 << i)) {
          oneAns[s[i] - 'a'] = 1;
        } else {
          oneAns[s[i] - 'a'] = 2;
        }
      }
      ans.push_back(oneAns);
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif