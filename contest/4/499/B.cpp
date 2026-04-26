
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

typedef long long ll;
class Solution {
 public:
  string sortVowels(const string& s) {
    map<char, pair<int, int>> m;
    for (int i = 0; i < s.size(); ++i) {
      char c = s[i];
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        if (m.count(c) == 0) {
          m[c] = {1, i};
        } else {
          m[c].first++;
        }
      }
    }
    vector<pair<char, pair<int, int>>> vowels(m.begin(), m.end());
    sort(vowels.begin(), vowels.end(), [](const auto& a, const auto& b) {
      if (a.second.first != b.second.first) {
        return a.second.first > b.second.first;
      }
      return a.second.second < b.second.second;
    });
    std::reverse(vowels.begin(), vowels.end());
    string result = s;
    int idx = 0;
    for (char c : s) {
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        result[idx++] = vowels.back().first;
        vowels.back().second.first--;
        if (vowels.back().second.first == 0) {
          vowels.pop_back();
        }
      } else {
        result[idx++] = c;
      }
    }
    return result;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif