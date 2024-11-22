
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

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Twitter {
  int t;
  vector<int> tweets;
  unordered_map<int, vector<int>> userTweets;
  unordered_map<int, unordered_set<int>> followers;

 public:
  Twitter() {
    const int N = 3 * 1e4;
    tweets.reserve(N);
  }

  void postTweet(int userId, int tweetId) {
    const int t = tweets.size();
    tweets.push_back(tweetId);
    userTweets[userId].push_back(t);
  }

  min_queue<int> que;
  void Add(const int userId) {
    const auto& timeLine = userTweets[userId];
    if (timeLine.empty()) return;
    for (int i = 0, j = timeLine.size() - 1; i < 10 && j >= 0; i++, j--) {
      que.push(timeLine[j]);
      if (que.size() > 10) {
        que.pop();
      }
    }
  }
  vector<int> getNewsFeed(int userId) {
    while (!que.empty()) que.pop();
    Add(userId);
    for (auto u : followers[userId]) {
      Add(u);
    }
    vector<int> ans;
    while (!que.empty()) {
      ans.push_back(tweets[que.top()]);
      que.pop();
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }

  void follow(int followerId, int followeeId) {
    followers[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    followers[followerId].erase(followeeId);
  }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  //   TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif