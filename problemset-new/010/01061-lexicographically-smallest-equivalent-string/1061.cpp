
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
const int N = 26;
class Solution {
  vector<int> pre;
  int Find(int a) {
    if (a == pre[a]) return a;
    return pre[a] = Find(pre[a]);
  }
  void Bind(int a, int b) {
    int A = Find(a);
    int B = Find(b);
    if (A > B) swap(A, B);
    if (A != B) {
      pre[a] = pre[b] = pre[B] = A;
    }
  }

 public:
  string smallestEquivalentString(const string& s1, const string& s2,
                                  string baseStr) {
    pre.resize(N);
    for (int i = 0; i < N; i++) {
      pre[i] = i;
    }
    for (size_t i = 0; i < s1.size(); i++) {
      Bind(s1[i] - 'a', s2[i] - 'a');
    }
    for (auto& c : baseStr) {
      c = 'a' + Find(c - 'a');
    }
    return baseStr;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(string s1, string s2, string baseStr, const string& ans) {
  TEST_SMP3(Solution, smallestEquivalentString, ans, s1, s2, baseStr);
}

int main() {
  Test("parker", "morris", "parser", "makkek");
  Test("hello", "world", "hold", "hdld");
  Test("leetcode", "programs", "sourcecode", "aauaaaaada");
  return 0;
}

#endif