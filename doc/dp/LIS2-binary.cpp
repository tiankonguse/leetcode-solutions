// 二维严格升序的最长子序列长度
// https://leetcode.cn/problems/maximize-fixed-points-after-deletions/description/

// 要求：第一维递增，第二维非递减
// 排序：第一维升序，第二维降序，使用 upper_bound
int Lis2(vector<pair<int, int>>& pts) {
  // x 升序；x 相同则 d 降序
  sort(pts.begin(), pts.end(), [](const auto& a, const auto& b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
  });

  // 在 d 上求最长非递减子序列
  vector<int> tails;
  for (auto& [x, d] : pts) {
    auto it = upper_bound(tails.begin(), tails.end(), d);
    if (it == tails.end()) {
      tails.push_back(d);
    } else {
      *it = d;
    }
  }

  return tails.size();
}

// 要求：第一维非递减，第二维递增
// 排序：默认，需要使用 lower_bound
int Lis2(vector<pair<int, int>>& pts) {
  sort(pts.begin(), pts.end());

  vector<int> tails;
  for (auto& [x, d] : pts) {
    auto it = lower_bound(tails.begin(), tails.end(), d);
    if (it == tails.end()) {
      tails.push_back(d);
    } else {
      *it = d;
    }
  }
  return tails.size();
}