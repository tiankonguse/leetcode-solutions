
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  enum { EVENT_ONLINE = 0, EVENT_OFFLINE = 1, EVENT_MESSAGE = 2 };
  vector<int> users;
  vector<int> ans;
  unordered_map<string, int> message_id;
  unordered_map<string, int> offline_id;
  void Init(int n) {
    users.resize(n, 1);
    ans.resize(n, 0);
    for (int i = 0; i < n; i++) {
      message_id["id" + std::to_string(i)] = i;
      offline_id[std::to_string(i)] = i;
    }
  }

  void Split(const string& str, vector<string>& vec, const char limit = ' ') {
    string buf;
    for (auto c : str) {
      if (c == limit) {
        vec.push_back(buf);
        buf.clear();
      } else {
        buf.push_back(c);
      }
    }
    if (!buf.empty()) {
      vec.push_back(buf);
      buf.clear();
    }
  }

 public:
  vector<int> countMentions(int n, vector<vector<string>>& events_) {
    Init(n);

    vector<tuple<int, int, string>> events;
    events.reserve(events_.size() * 2);
    for (auto& e : events_) {
      const string& eventType = e[0];
      const string& eventTime = e[1];
      const string& ids = e[2];
      const int t = stoi(eventTime);
      if (eventType == "MESSAGE") {
        events.push_back({t, EVENT_MESSAGE, ids});
      } else {
        events.push_back({t, EVENT_OFFLINE, ids});
        events.push_back({t + 60, EVENT_ONLINE, ids});
      }
    }
    sort(events.begin(), events.end());

    for (auto& [eventTime, eventType, ids] : events) {
      if (eventType == EVENT_ONLINE) {
        users[offline_id[ids]] = 1;
      } else if (eventType == EVENT_OFFLINE) {
        users[offline_id[ids]] = 0;
      } else {
        if (ids == "ALL") {
          for (int i = 0; i < n; i++) {
            ans[i]++;
          }
        } else if (ids == "HERE") {
          for (int i = 0; i < n; i++) {
            if (users[i]) {
              ans[i]++;
            }
          }
        } else {
          vector<string> vec;
          Split(ids, vec);
          for (auto& s : vec) {
            ans[message_id[s]]++;
          }
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif