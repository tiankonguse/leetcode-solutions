#include <bits/stdc++.h>
using namespace std;

// https://oi-wiki.org/string/manacher/
// s 原始字符串; ss 预处理后的字符串;  p 各中心的半径
void Manacher(const string& s, string& ss, vector<int>& p) {
  int n = s.size();
  int nn = n * 2 + 2;
  ss.resize(nn);
  p.resize(nn);

  ss[0] = '$';
  ss[nn - 1] = '#';
  for (int i = 0; i < n; i++) {
    ss[i * 2 + 1] = '#';
    ss[i * 2 + 2] = s[i];
  }
  int r = 0, id = 0;  // 到达最远 r 时，中心为 id, (id-r, id+r)
  for (int i = 1; i < nn; i++) {
    p[i] = 1;
    if (r > i) {
      p[i] = min(p[2 * id - i], r - i);
    }
    while (i + p[i] < nn && i - p[i] > 0 && ss[i + p[i]] == ss[i - p[i]]) {
      p[i]++;
    }
    if (i + p[i] > r) {
      r = i + p[i];
      id = i;
    }
  }
}