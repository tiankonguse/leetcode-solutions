// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;

static const auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin.tie(nullptr);
  return nullptr;
}();

#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

const int maxBit = 7;
const vector<ll> bits = {1, 10, 100, 1000, 10000, 100000, 1000000};
const vector<vector<int>> A3 = {{1, 2, 0}, {2, 0, 1}};
class Solution {
  int SwapBit(const int v, const int i, const int j) {
    const int vi = v / bits[i] % 10;
    const int vj = v / bits[j] % 10;
    return v - vi * bits[i] - vj * bits[j] + vi * bits[j] + vj * bits[i];
  }

 public:
  int countPairs(vector<int>& nums) {
    const int n = nums.size();
    int ans = 0;
    unordered_map<int, int> valNum;
    for (const auto v : nums) {
      valNum[v]++;
    }
    // 不做任何交换
    for (const auto v : nums) {
      ans += valNum[v] - 1;  // 需要排除自己
    }

    // 交换 2 个位置
    for (const auto v : nums) {
      for (int i = 0; i < maxBit; i++) {
        for (int j = i + 1; j < maxBit; j++) {
          // 交换 v 的 第 i 和 第 j 位
          int vi = v / bits[i] % 10;
          int vj = v / bits[j] % 10;
          if (vi == vj) continue;
          int V = SwapBit(v, i, j);
          if (valNum.count(V)) {
            ans += valNum[V];
          }
        }
      }
    }

    // 交换三个位置
    for (const auto v : nums) {
      for (int i = 0; i < maxBit; i++) {
        for (int j = i + 1; j < maxBit; j++) {
          for (int k = j + 1; k < maxBit; k++) {
            int vi = v / bits[i] % 10;
            int vj = v / bits[j] % 10;
            int vk = v / bits[k] % 10;
            if (vi == vj || vi == vk || vj == vk) {
              continue;  // 有相同的，等价与交换两个位置
            }
            vector<int> indexs = {i, j, k};
            for (auto& a3 : A3) {  // 只有两种情况
              int V = v;
              for (int p = 0; p < indexs.size(); p++) {
                int vOld = v / bits[indexs[p]] % 10;
                V -= vOld * bits[indexs[p]];
              }

              for (int p = 0; p < indexs.size(); p++) {
                int vNew = v / bits[indexs[a3[p]]] % 10;
                V += vNew * bits[indexs[p]];
              }

              if (valNum.count(V)) {
                ans += valNum[V];
              }
            }
          }
        }
      }
    }

    // 交换四个位置，两两交换
    for (const auto v : nums) {
      for (int a = 0; a < maxBit; a++) {
        for (int b = a + 1; b < maxBit; b++) {
          for (int c = b + 1; c < maxBit; c++) {
            for (int d = c + 1; d < maxBit; d++) {
              vector<int> indexs = {a, b, c, d};
              vector<int> values;
              for (auto k : indexs) {
                values.push_back(v / bits[k] % 10);
              }

              int tmp = 0;

              for (int i = 1; i < 4; i++) {  // a 分别后面三个位置交换
                swap(indexs[1], indexs[i]);
                swap(values[1], values[i]);

                if (values[0] != values[1] && values[2] != values[3]) {
                  int V = v;
                  V = SwapBit(V, indexs[0], indexs[1]);
                  V = SwapBit(V, indexs[2], indexs[3]);
                  if (valNum.count(V)) {
                    tmp += valNum[V];
                  }
                }

                swap(indexs[1], indexs[i]);
                swap(values[1], values[i]);
              }

              // aabb 的情况，会导致重复多算一次，需要减半
              sort(values.begin(), values.end());
              if (values[0] == values[1] && values[2] == values[3]) {
                tmp /= 2;
              }

              ans += tmp;
            }
          }
        }
      }
    }

    return ans / 2;
  }
};