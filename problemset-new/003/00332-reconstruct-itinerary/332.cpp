
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  vector<string> strs;
  unordered_map<string, int> h;
  vector<vector<int>> g;
  int n;

  int Hash(const string& s) {
    if (h.count(s)) {
      return h[s];
    }
    strs.push_back(s);
    return h[s] = strs.size() - 1;
  }
  vector<int> vals;
  vector<int> nexts;
  vector<int> pres;
  int index = 0;

  int Add(int s) {
    int oldIndex = index;
    index++;
    vals[oldIndex] = s;
    return oldIndex;
  }

  void Bind(int a, int b) {
    nexts[a] = b;
    pres[b] = a;
  }
  // first -> second
  int Traver(int first) {
    MyPrintf("-->first=%d vals=%d[%s] size=%d pre=%d next=%d\n", first,
             vals[first], strs[vals[first]].data(), int(g[vals[first]].size()),
             pres[first], nexts[first]);
    while (g[vals[first]].size() > 0) {
      int c = g[vals[first]].back();
      g[vals[first]].pop_back();
      const int second = Add(c);
      Bind(first, second);
      first = second;
      MyPrintf("->first=%d vals=%d[%s] size=%d pre=%d next=%d\n", first,
               vals[first], strs[vals[first]].data(),
               int(g[vals[first]].size()), pres[first], nexts[first]);
    }
    return first;
  }

 public:
  vector<string> findItinerary(const vector<vector<string>>& tickets) {  //
    MyPrintf("----begin-----\n");
    int m = tickets.size();
    for (auto& ticket : tickets) {
      for (auto& s : ticket) {
        Hash(s);
      }
    }
    n = strs.size();
    g.resize(n);
    for (auto& ticket : tickets) {
      const int a = Hash(ticket[0]);
      const int b = Hash(ticket[1]);
      g[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
      sort(g[i].begin(), g[i].end(), [that = this](int a, int b) {
        return that->strs[a] > that->strs[b];
      });
      MyPrintf("i=%d[%s] ", i, strs[i].data());
      for (auto& j : g[i]) {
        MyPrintf(" %d[%s]", j, strs[j].data());
      }
      MyPrintf("\n");
    }

    vals.resize(m + 10, -1);
    nexts.resize(m + 10, -1);
    pres.resize(m + 10, -1);

    int s = Hash("JFK");
    const int first = Add(s);
    MyPrintf("first=%d\n", first);
    const int last = Traver(first);
    MyPrintf("index=%d m=%d last=%d\n", index, m, last);
    while (index <= m) {
      // 从最后一个向前找到最后一个非空节点
      int mid = last;
      while (mid != -1 && vals[mid] != -1 && g[vals[mid]].size() == 0) {
        mid = pres[mid];
      }
      MyPrintf("mid=%d\n", mid);

      // mid -> first
      int val = g[vals[mid]].back();
      g[vals[mid]].pop_back();
      const int midFirst = Add(val);  // 首个节点
      MyPrintf("midFirst=%d\n", midFirst);
      int midLast = Traver(midFirst);
      MyPrintf("midLast=%d\n", midLast);
      // first-> ... -> mid -> ... last
      // mid : midFirst -> ... -> midLast
      MyPrintf("first=%d mid=%d last=%d\n", first, mid, last);
      MyPrintf("mid=%d midFirst=%d midLast=%d\n", mid, midFirst, midLast);
      const int nextMid = nexts[mid];
      MyPrintf("midLast=%d nextMid=%d\n", midLast, nextMid);
      Bind(midLast, nextMid);
      Bind(mid, midFirst);
      MyPrintf("mid=%d midFirst=%d\n", mid, midFirst);
      MyPrintf("next[midLast]=%d pre[midLast]=%d\n", nexts[midLast],
               pres[midLast]);
      MyPrintf("next[nextMid]=%d pre[nextMid]=%d\n", nexts[nextMid],
               pres[nextMid]);
      MyPrintf("next[mid]=%d pre[mid]=%d\n", nexts[mid], pres[mid]);
      MyPrintf("next[midFirst]=%d pre[midFirst]=%d\n", nexts[midFirst],
               pres[midFirst]);
      MyPrintf("last index=%d m=%d\n", index, m);
    }

    vector<string> ans;
    ans.reserve(m + 1);

    int it = first;
    while (it != -1 && vals[it] != -1) {
      ans.push_back(strs[vals[it]]);
      it = nexts[it];
    }
    MyPrintf("ans[%d] ", int(ans.size()));
    for (auto& v : ans) {
      MyPrintf(" [%s]", v.data());
    }
    MyPrintf("\n");
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<string>> tickets, const vector<string>& ans) {
  TEST_SMP1(Solution, findItinerary, ans, tickets);
}

int main() {
  Test({{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}},
       {"JFK", "NRT", "JFK", "KUL"});
  Test({{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}},
       {"JFK", "MUC", "LHR", "SFO", "SJC"});
  Test({{"JFK", "SFO"},
        {"JFK", "ATL"},
        {"SFO", "ATL"},
        {"ATL", "JFK"},
        {"ATL", "SFO"}},
       {"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"});

  return 0;
}

#endif