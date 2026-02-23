
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
    int scoreDifference(vector<int>& nums) {
        int ans[2] = {0, 0};
        int index = 0;
        int n = nums.size();
        for(int i=0;i<n;i++){
          const int v = nums[i];
          if(v%2 == 1){
            index = 1 - index;
          }
          if(i % 6 == 5){
            index = 1 - index;
          }
          ans[index] += v;
        }
        return ans[0] - ans[1];
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