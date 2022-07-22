// 线段合并

class MapSeg {
  map<int, int> m;  // r => l

 public:
  int Query(int l, int r) {  // 查询 [l,r] 的交集长度
    int num = 0;
    while (l <= r) {
      auto it = m.lower_bound(l);
      if (it == m.end()) break;

      auto [R, L] = *it;

      int tmpL = max(l, L);
      int tmpR = min(r, R);
      if (tmpL > tmpR) break;  // 没有交集

      num += tmpR - tmpL + 1;

      l = tmpR + 1;
    }
    return num;
  }

  void Insert(int l, int r) {  // 合并线段
    while (1) {
      auto it = m.lower_bound(l - 1);
      if (it == m.end()) break;

      auto [R, L] = *it;
      if (L > r + 1) break;

      l = min(l, L);
      r = max(r, R);
      m.erase(it);
    }
    m[r] = l;
  }
};