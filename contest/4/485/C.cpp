
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

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */
class AuctionSystem {
  unordered_map<int, map<int, set<int>>> itemMaxCost;
  unordered_map<int, unordered_map<int, int>> itemUserCost;

 public:
  AuctionSystem() {}

  void addBid(int userId, int itemId, int bidAmount) {  //
    updateBid(userId, itemId, bidAmount);
  }

  void updateBid(int userId, int itemId, int newAmount) {  //
    auto& maxCost = itemMaxCost[itemId];
    auto& userCost = itemUserCost[itemId];
    if (userCost.count(userId)) {
      removeBid(userId, itemId);
    }
    userCost[userId] = newAmount;
    maxCost[newAmount].insert(userId);
  }

  void removeBid(int userId, int itemId) {  //
    auto& maxCost = itemMaxCost[itemId];
    auto& userCost = itemUserCost[itemId];
    if (userCost.count(userId) == 0) {
      return;
    }
    int cost = userCost[userId];
    maxCost[cost].erase(userId);
    if (maxCost[cost].empty()) {
      maxCost.erase(cost);
    }
    userCost.erase(userId);
  }

  int getHighestBidder(int itemId) {
    if (itemMaxCost[itemId].empty()) {
      return -1;
    }
    return *itemMaxCost[itemId].rbegin()->second.rbegin();
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