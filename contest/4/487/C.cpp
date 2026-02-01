
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
class RideSharingSystem {
  unordered_map<int, int> driverFlag;
  unordered_map<int, int> riderFlag;
  map<int, int> drivers;
  map<int, int> riders;
  int t = 0;

 public:
  RideSharingSystem() { t = 0; }

  void addRider(int riderId) {
    t++;
    riderFlag[riderId] = t;
    riders[t] = riderId;
  }

  void addDriver(int driverId) {
    t++;
    driverFlag[driverId] = t;
    drivers[t] = driverId;
  }
  void cancelRider(int riderId) {
    if (riderFlag.count(riderId)) {
      riders.erase(riderFlag[riderId]);
      riderFlag.erase(riderId);
    }
  }
  void cancelDriver(int driverId) {
    if (driverFlag.count(driverId)) {
      drivers.erase(driverFlag[driverId]);
      driverFlag.erase(driverId);
    }
  }

  vector<int> matchDriverWithRider() {
    if (drivers.empty() || riders.empty()) {
      return {-1, -1};
    }
    int driver = drivers.begin()->second;
    int rider = riders.begin()->second;
    cancelRider(rider);
    cancelDriver(driver);
    return {driver, rider};
  }
};

/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * RideSharingSystem* obj = new RideSharingSystem();
 * obj->addRider(riderId);
 * obj->addDriver(driverId);
 * vector<int> param_3 = obj->matchDriverWithRider();
 * obj->cancelRider(riderId);
 */

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif