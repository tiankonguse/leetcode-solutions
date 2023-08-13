/*************************************************************************
    > File Name: D.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月28日 18:28:51
 ************************************************************************/

// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  vector<set<int>> vecGraph;
  map<int, int> stateSet;  // 空图 到 (start, state) 到最小步骤
  int n;

 public:
  int shortestPathLength(vector<vector<int>>& graph) {
    n = graph.size();
    if (n <= 1) {
      return 0;
    }
    vecGraph.resize(n);
    const int MAX_BIT = 12;

    for (int i = 0; i < n; i++) {
      auto& path = graph[i];
      for (int j = 0; j < path.size(); j++) {
        vecGraph[i].insert(path[j]);
        vecGraph[path[j]].insert(i);
      }
    }
    queue<int> que;

    int startState = 0;
    for (int i = 0; i < n; i++) {
      startState = (i << MAX_BIT) | (1 << i);
      stateSet[startState] = 1;
      que.push(startState);
    }

    int start = 0, state = 0;
    int newStart, newState = 0;
    int step = 0;
    while (!que.empty()) {
      startState = que.front();
      que.pop();

      start = startState >> MAX_BIT;
      state = startState ^ (start << MAX_BIT);
      step = stateSet[startState];

      auto& nodePath = vecGraph[start];
      for (auto it = nodePath.begin(); it != nodePath.end(); it++) {
        newStart = *it;
        newState = state | (1 << newStart);
        startState = (newStart << MAX_BIT) | newState;
        if (stateSet.find(startState) != stateSet.end()) {
          continue;
        }
        stateSet[startState] = step + 1;
        que.push(startState);

        if (newState + 1 == (1 << n)) {
          return step;
        }
      }
    }

    return -1;
  }
};

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
  vector<vector<int>> first;
  int expectAns;

  first = {{1}, {0}};
  expectAns = 1;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{1, 2, 3}, {0}, {0}, {0}};
  expectAns = 4;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2}};
  expectAns = 4;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{}};
  expectAns = 0;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{1, 4},    {0, 3, 4, 7, 9}, {6, 10}, {1, 10}, {1, 0}, {6},
           {7, 2, 5}, {6, 1, 8},       {7},     {1},     {2, 3}};
  expectAns = 12;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{1}, {0, 2, 6}, {1, 3}, {2}, {5}, {4, 6}, {1, 5, 7}, {6}};
  expectAns = 9;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{3}, {3}, {3, 5}, {0, 1, 2, 6}, {6}, {2}, {3, 4}};
  expectAns = 8;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{6, 7}, {6}, {6}, {5, 6}, {6}, {3}, {2, 0, 3, 4, 1}, {0}};
  expectAns = 10;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
      {0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11}, {0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11},
      {0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11}, {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11},
      {0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11}, {0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11},
      {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11},
      {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11},  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  expectAns = 11;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  first = {{2, 3}, {7}, {0, 6}, {0, 4, 7}, {3, 8}, {7}, {2}, {5, 3, 1}, {4}};
  expectAns = 11;
  TEST_SMP1(Solution, shortestPathLength, expectAns, first);

  return 0;
}
