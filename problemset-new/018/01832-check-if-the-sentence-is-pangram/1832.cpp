// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool checkIfPangram(string& str) {
    return unordered_set<char>(str.begin(), str.end()).size() == 26;
  }
};
