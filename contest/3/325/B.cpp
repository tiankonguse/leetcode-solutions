// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool Check(const string& s, int k) {
    vector<int> nums(3, 0);
    for (auto c : s) {
      nums[c - 'a']++;
    }
    sort(nums.begin(), nums.end());
    return nums.front() >= k;
  }

  int n;
  int N;
  int k;
  string S;

  struct Node {
    vector<int> v;
    int flag;
    Node() {
      flag = false;
      v.resize(3, 0);
    }
  };
  vector<Node> nums;

  int Solver(const string& s) {
    S = s;
    S.append(s);

    n = s.length();
    N = S.length();

    nums.resize(N + 1);

    for (int i = 1; i <= N; i++) {
      int v = S[i - 1] - 'a';
      nums[i] = nums[i - 1];
      nums[i].v[v]++;
    }

    int ans = n;

    printf("s=%s\n", S.c_str());
    for (int i = 1; i <= n + 1; i++) {
      // 左边取 [i,n]
      Node base;
      if (i <= n) {
        for (int j = 0; j < 3; j++) {
          base.v[j] = nums[n].v[j] - nums[i - 1].v[j];
        }
        if (base.v[0] >= k && base.v[1] >= k && base.v[2] >= k) {
          printf("i=%d ok, tmp=%d\n", i, n - i + 1);
          ans = min(ans, n - i + 1);
          continue;
        }
      }

      base.v = nums[i - 1].v;
      for (auto& v : base.v) {
        v += k;
      }

      base.flag = true;
      auto it = Search(i, base);
      if (it == N + 1) break;
      int dis = it - i + 1;
      printf("i=%d dis=%d %s\n", i, dis, S.substr(i - 1, dis).c_str());
      ans = min(ans, dis);
    }

    return ans;
  }

  bool Less(Node& a, Node& b) {
    if (a.v[0] <= b.v[0] && a.v[1] <= b.v[1] && a.v[2] <= b.v[2]) {
      return true;
    }
    if (a.v[0] >= b.v[0] && a.v[1] >= b.v[1] && a.v[2] >= b.v[2]) {
      return false;
    }
    return false;
  }

  int Search(int pos, Node& base) {
    int l = pos, r = N + 1;  // [l, r)

    while (l < r) {
      int mid = (l + r) / 2;
      if (Less(base, nums[mid])) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }

 public:
  int takeCharacters(const string& s, int k) {
    if (k == 0) return 0;
    this->k = k;
    if (!Check(s, k)) {
      return -1;
    }
    return Solver(s);
  }
};

/*
"aabaaaacaabc"
2
"a"
1
"acba"
1
"ccbabcc"
1
*/