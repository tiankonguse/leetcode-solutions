#include <bits/stdc++.h>
using namespace std;

// https://oi-wiki.org/string/manacher/
// s 原始字符串; ss 预处理后的字符串;  p 各中心的半径
// 最大回文串长度为 max(p[i]-1)
// #A#: 字符为中心, p[i] = 2, 总长度为 L=p[i]*2-1, 字符个数为 (L-1)/2=p[i]-1
// #A#A#: # 为中心， p[i] = 3, 总长度为 L=p[i]*2-1, 字符个数为 (L-1)/2=p[i]-1
void Manacher(const string& s, string& ss, vector<int>& p) {
  int n = s.size();
  int nn = n * 2 + 1;
  ss.resize(nn);
  p.resize(nn);

  ss[nn - 1] = '#';
  for (int i = 0; i < n; i++) {
    ss[i * 2] = '#';
    ss[i * 2 + 1] = s[i];
  }
  int r = 0, id = 0;  // 到达最远 r 时，中心为 id, R = r - id,  (id-R, id+R)
  for (int i = 0; i < nn; i++) {
    p[i] = 1;
    if (r > i) {  // 优化，根据对称性快速找到确定的半径
      // D = i - id
      // ii = id - D
      p[i] = min(p[2 * id - i], r - i);
    }
    while (i + p[i] < nn && i - p[i] >= 0 && ss[i + p[i]] == ss[i - p[i]]) {
      p[i]++;
    }
    if (i + p[i] > r) {
      r = i + p[i];
      id = i;
    }
  }
}