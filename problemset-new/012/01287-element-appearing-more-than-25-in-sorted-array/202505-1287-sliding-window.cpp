
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
 // The Solution::findSpecialInteger function takes a reference to a vector of integers and returns the first integer that appears more than 25% of the time in the sorted array. 
 // It uses a sliding window approach to efficiently check for such an element, returning -1 if no such element is found.
  int findSpecialInteger(vector<int>& arr) {
    int n = arr.size();
    int threshold = n / 4;
    for (int i = 0; i < n; i++) {
      if (i + threshold < n && arr[i] == arr[i + threshold]) {
        return arr[i];
      }
    }
    return -1;
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