
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
class TopVotedCandidate {
  unordered_map<int, int> personVotes;
  map<int, int> votesPeron;
  map<int, int> timesPerson;

 public:
  TopVotedCandidate(vector<int>& persons, vector<int>& times) {
    const int n = persons.size();
    for (int i = 0; i < n; i++) {
      const int p = persons[i];
      const int t = times[i];
      personVotes[p]++;
      votesPeron[personVotes[p]] = p;
      timesPerson[t] = votesPeron.rbegin()->second;
    }
  }


  int q(int t) {
    auto it = timesPerson.upper_bound(t);
    return prev(it)->second;
  }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
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