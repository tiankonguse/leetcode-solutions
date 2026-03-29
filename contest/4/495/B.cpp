
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
class EventManager {
  map<int, set<int>> mp;                  // priority -> set of eventId
  unordered_map<int, int> eventPriority;  // eventId -> priority
 public:
  EventManager(vector<vector<int>>& events) {
    for (auto& event : events) {
      int eventId = event[0];
      int priority = event[1];
      mp[priority].insert(eventId);
      eventPriority[eventId] = priority;
    }
  }
  void RemoveEvent(int eventId) {
    if (eventPriority.find(eventId) != eventPriority.end()) {
      int priority = eventPriority[eventId];
      mp[priority].erase(eventId);
      if (mp[priority].empty()) {
        mp.erase(priority);
      }
      eventPriority.erase(eventId);
    }
  }

  void updatePriority(int eventId, int newPriority) {
    if (eventPriority.find(eventId) != eventPriority.end()) {
      RemoveEvent(eventId);
      mp[newPriority].insert(eventId);
      eventPriority[eventId] = newPriority;
    }
  }

  int pollHighest() {
    if (mp.empty()) {
      return -1;
    }
    auto it = mp.rbegin();  
    int highestPriority = it->first;
    auto& eventSet = it->second;
    int eventId = *eventSet.begin(); 
    RemoveEvent(eventId);
    return eventId;
  }
};

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
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