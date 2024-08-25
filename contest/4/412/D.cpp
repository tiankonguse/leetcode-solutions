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

const int N = 1000;
const int NN = N * N;
vector<int> diff[N][N];
int diffInit = 0;

vector<int> bits10 = {1, 10, 100, 1000, 10000};

vector<int> H;

void Init() {
  if (diffInit) return;
  vector<int> bound = {10, 100, 1000};
  for (auto n : bound) {
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        diff[i][j] = diff[i / 10][j / 10];
        for (auto& v : diff[i][j]) {
          v++;
        }
        if (i % 10 != j % 10) {
          diff[i][j].push_back(0);
        }
        diff[j][i] = diff[i][j];
      }
    }
  }

  H.resize(50001);
  diffInit = 1;
}

unordered_map<int, int> valToHash;
class Solution {
  vector<int> aa, bb;
  inline bool CheckEx(int i, int j) { return aa[i] == bb[j] && aa[j] == bb[i]; }
  bool Check(const int a, const int b) {
    if (a == b) return true;
    const int a_nn = a / NN, b_nn = b / NN;
    const int a_n_n = a / N % N, b_n_n = b / N % N;
    const int a_n = a % N, b_n = b % N;

    const int diffNum = diff[a_nn][b_nn].size() + diff[a_n_n][b_n_n].size() +
                        diff[a_n][b_n].size();
    if (diffNum == 2 || diffNum == 3) {
      return true;  // hash 相同，2~3个肯定有答案
    }
    if (diffNum >= 5) return false;  // 肯定没答案

    aa.clear();
    bb.clear();
    // myprintf("a_nn=%d b_nn=%d size=%d\n", a_nn, b_nn,
    // diff[a_nn][b_nn].size());
    if (diff[a_nn][b_nn].size()) {  // 最高位
      for (auto i : diff[a_nn][b_nn]) {
        aa.push_back(a_nn / bits10[i] % 10);
        bb.push_back(b_nn / bits10[i] % 10);
      }
    }
    // myprintf("a_n_n=%d b_n_n=%d size=%d\n", a_n_n, b_n_n,
    //          diff[a_n_n][b_n_n].size());
    if (diff[a_n_n][b_n_n].size()) {  // 中间三位
      for (auto i : diff[a_n_n][b_n_n]) {
        aa.push_back(a_n_n / bits10[i] % 10);
        bb.push_back(b_n_n / bits10[i] % 10);
      }
    }
    // myprintf("a_n=%d b_n=%d size=%d\n", a_n, b_n, diff[a_n][b_n].size());
    if (diff[a_n][b_n].size()) {  // 最低三位
      for (auto i : diff[a_n][b_n]) {
        aa.push_back(a_n / bits10[i] % 10);
        bb.push_back(b_n / bits10[i] % 10);
      }
    }
    // myprintf("aa[%d]: ", aa.size());
    // for (auto v : aa) {
    //   myprintf("%d ", v);
    // }
    // myprintf("\n", "");
    // myprintf("bb[%d]: ", bb.size());
    // for (auto v : bb) {
    //   myprintf("%d ", v);
    // }
    // myprintf("\n", "");
    // 四个排序后保证相等，随便挑两个匹配的化，剩余两个肯定匹配
    for (int i = 1; i < 4; i++) {
      if (CheckEx(0, i)) {
        return true;
      }
    }
    // myprintf("check a=%d b=%d ret=%d \n", a, b, ret);
    return false;
  }

  vector<int> bits;
  int Hash(const int V) {
    int v = V;
    if (valToHash.count(v)) {
      return valToHash[v];
    }
    bits.clear();
    bits.resize(10, 0);
    while (v) {
      bits[v % 10]++;
      v /= 10;
    }
    int h = 0;
    for (int i = 1; i <= 9; i++) {
      int v = bits[i];
      while (v--) {
        h = h * 10 + i;
      }
    }
    return valToHash[V] = h;
  }

 public:
  int countPairs(vector<int>& nums) {
    Init();
    int n = nums.size();
    int ans = 0;
    H.resize(n);
    for (int i = 0; i < n; i++) {
      H[i] = Hash(nums[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (H[i] == H[j] && Check(nums[i], nums[j])) {
          ans++;
        }
      }
    }

    return ans;
  }
};