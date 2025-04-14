
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

// 超出内存限制
typedef long long ll;
class Router {
  int n;

  std::list<tuple<int, int, int>> packets;    // (source, destination, timestamp)
  unordered_map<int, vector<int>> packetMap;  // destination -> timestamp, 永远不删除
  unordered_map<int, int> destinationIndex;
  unordered_set<ll> packetFlag;  // 只储存当前时间戳的包
  int flagTime = 0;

 public:
  Router(int memoryLimit) { n = memoryLimit; }

  bool addPacket(int source, int destination, int timestamp) {
    if (flagTime != timestamp) {
      flagTime = timestamp;
      packetFlag.clear();
    }
    ll h = (ll(source) << 32) + destination;

    tuple<int, int, int> packet = make_tuple(source, destination, timestamp);
    if (packetFlag.count(h) == 1) {
      return false;
    }

    if (packets.size() == n) {
      forwardPacket();
    }
    packets.push_back(packet);
    packetFlag.insert(h);
    packetMap[destination].push_back(timestamp);
    return true;
  }

  vector<int> forwardPacket() {  // 出队一个包
    if (packets.empty()) {
      return vector<int>();
    }
    auto [source, destination, timestamp] = packets.front();
    packets.pop_front();
    ll h = (ll(source) << 32) + destination;
    if (flagTime == timestamp) {
      packetFlag.erase(h);
    }
    destinationIndex[destination]++;
    if (destinationIndex[destination] == packetMap[destination].size()) {
      packetMap[destination].clear();
      destinationIndex.erase(destination);
    }
    return {source, destination, timestamp};
  }

  int getCount(int destination, int startTime, int endTime) {
    if (packetMap.find(destination) == packetMap.end()) {
      return 0;
    }
    auto& packet = packetMap[destination];
    int index = destinationIndex[destination];
    auto begin = packet.begin() + index;
    auto end = packet.end();
    // 查找区间 [index, count) 内，值满足 [startTime， endTime]的个数
    int left = lower_bound(begin, end, startTime) - begin;
    int right = upper_bound(begin, end, endTime) - begin;
    return right - left;
  }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif