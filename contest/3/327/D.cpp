// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using max_queue = priority_queue<T>;

vector<vector<int>> nodeTime;
int leftToRight(int i) { return nodeTime[i][0]; }
int pickOld(int i) { return nodeTime[i][1]; }
int rightToLeft(int i) { return nodeTime[i][2]; }
int putNew(int i) { return nodeTime[i][3]; }

struct Node {
  int i = 0;
  ll Cost() const { return leftToRight(i) + rightToLeft(i); }
  // 小于是最大堆，大于是最小堆
  bool operator<(const Node& b) const {
    auto& a = *this;
    if (a.Cost() != b.Cost()) {
      return a.Cost() < b.Cost();
    } else {
      return a.i < b.i;
    }
  }
};

enum Event {  //
  EventToLeftQue = 0,
  EventToRightQue = 1
};

class Solution {
 public:
  max_queue<Node> leftQue;
  max_queue<Node> rightQue;
  map<ll, vector<int>> leftEvent;   // 时间线上的事件列表
  map<ll, vector<int>> rightEvent;  // 时间线上的事件列表

  ll t = 0;
  void ProcessEvent(map<ll, vector<int>>& vents, max_queue<Node>& que) {
    while (vents.size() > 0 && vents.begin()->first <= t) {
      ll T = vents.begin()->first;
      for (int i : vents[T]) {
        que.push(Node{i});
      }
      vents.erase(T);
    }
  }

  int findCrossingTime(int n, int k, vector<vector<int>>& time_) {
    nodeTime.swap(time_);

    for (int i = 0; i < k; i++) {
      leftQue.push(Node{i});
      // printf("i=%d last=%d\n", i, leftQue.top().i);
    }

    t = 0;
    while (n > 0 || rightQue.size() > 0 || rightEvent.size() > 0) {
      // 到达时间 t, 历史事件进行整理

      ProcessEvent(leftEvent, leftQue);
      ProcessEvent(rightEvent, rightQue);

      // 规则1：
      // -如果没有正在过桥的工人，那么在桥右边等待的工人可以先过桥。
      // -如果同时有多个工人在右边等待，那么 效率最低 的工人会先过桥。
      if (rightQue.size() > 0) {
        int i = rightQue.top().i;
        rightQue.pop();
        t += rightToLeft(i);
        ll T = t + putNew(i);
        leftEvent[T].push_back(i);
        // printf("rightQue i=%d t=%lld, event= %lld\n", i, t, T);
        continue;
      }

      // 规则2
      // -如果没有正在过桥的工人，且桥右边也没有在等待的工人，同时旧仓库还剩下至少一个箱子需要搬运，此时在桥左边的工人可以过桥。
      // -如果同时有多个工人在左边等待，那么 效率最低 的工人会先过桥。
      if (n > 0 && leftQue.size() > 0) {
        int i = leftQue.top().i;
        leftQue.pop();
        t += leftToRight(i);
        ll T = t + pickOld(i);
        rightEvent[T].push_back(i);
        n--;
        // printf("rightQue i=%d t=%lld, event= %lld\n", i, t, T);
        continue;
      }

      // 此时没有人等待过桥，大家都在仓库去桥的路上，快进时间到最近的事件
      if (leftEvent.size() > 0 || rightEvent.size() > 0) {
        if (leftEvent.size() == 0) {
          t = rightEvent.begin()->first;
        } else if (rightEvent.size() == 0) {
          t = leftEvent.begin()->first;
        } else {
          t = min(rightEvent.begin()->first, leftEvent.begin()->first);
        }

        // printf("fast go to T=%lld\n", t);
      }
    }
    return t;
  }
};