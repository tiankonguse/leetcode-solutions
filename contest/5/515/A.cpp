
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
    int nearestDrone(vector<vector<int>>& drones, vector<int>& target) {
        int ans = -1;
        int minDist = INT_MAX;
        int n = drones.size();
        int tx = target[0], ty = target[1];
        for(int i=0;i<n;i++){
          int x = drones[i][0], y = drones[i][1], d = drones[i][2];
          int dist = abs(x - tx) + abs(y - ty);
          if (dist <= d && dist < minDist) {
            ans = i;
            minDist = dist;
          }
        }
        return ans;
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