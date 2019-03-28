/*************************************************************************
    > File Name: D.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月28日 18:28:51
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    vector<set<int> > vecGraph;
    vector<int> nodeNum;
    vector<int> have;
    vector<int> ansPath;

    map<int, int> stateSet;
    int n;

    void add(int start) {
        ansPath.push_back(start);
        nodeNum[start]--;
        have[start]++;
    }

    void del(int start) {
        have[start]--;
        nodeNum[start]++;
        ansPath.pop_back();
    }


    int dfs(int start, int dep = 0, int ansNum = 0, int state = 0) {
        if(dep > 2*n) {
            return 2*n;
        }
        if(dep > 10 || start > 5){
            //printf("start=%d dep=%d ansNum=%d\n", start, dep, ansNum);
            //output("ansPath", ansPath);
        }
        state |= (1<<start);
        add(start);
        if(have[start] == 1) {
            ansNum++;
        }


        if(ansNum >= n) {
            del(start);
            output("ansPath", ansPath);
            return 0;
        }

        int startState =  start << 14 | state;
        if(stateSet.find(startState) != stateSet.end()) {
            del(start);
            return stateSet[startState];
        }

        auto& nodePath = vecGraph[start];
        int minAns = 2*n;
        int tmpAns = 0;
        for(auto it = nodePath.begin(); it != nodePath.end(); it++) {
            tmpAns = 1 + dfs(*it, dep + 1, ansNum, state);
            minAns = min(minAns, tmpAns);
        }
        //printf("start=%d state=%02X ans=%d\n", start, state, minAns);
        del(start);
        return stateSet[startState] = minAns;;

    }

public:
    int shortestPathLength(vector<vector<int>>& graph) {
        n = graph.size();
        if(n <= 1) {
            return 0;
        }
        nodeNum.resize(n);
        vecGraph.resize(n);
        have.resize(n, 0);

        for(int i=0; i<n; i++) {
            auto& path = graph[i];
            for(int j=0; j<path.size(); j++) {
                vecGraph[i].insert(path[j]);
                vecGraph[path[j]].insert(i);
            }
        }

        for(int i=0; i<n; i++) {
            nodeNum[i] = vecGraph[i].size();
        }

        int ans = n * 2;
        for(int i=0; i<n; i++) {
            printf("i=%d\n",i);
            ans = min(dfs(i), ans);
        }
        return ans;
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


//    first = {{1},{0}};
//    expectAns = 1;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//    first = {{1,2,3},{0},{0},{0}};
//    expectAns = 4;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//    first = {{1},{0,2,4},{1,3,4},{2},{1,2}};
//    expectAns = 4;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//
//
//
//    first = {{}};
//    expectAns = 0;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//    first = {{1,4},{0,3,4,7,9},{6,10},{1,10},{1,0},{6},{7,2,5},{6,1,8},{7},{1},{2,3}};
//    expectAns = 12;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//
//    first = {{1},{0,2,6},{1,3},{2},{5},{4,6},{1,5,7},{6}};
//    expectAns = 9;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//
//    first = {{3},{3},{3,5},{0,1,2,6},{6},{2},{3,4}};
//    expectAns = 8;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//
//    first = {{6,7},{6},{6},{5,6},{6},{3},{2,0,3,4,1},{0}};
//    expectAns = 10;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);
//
//    first = {{1,2,3,4,5,6,7,8,9,10,11},{0,2,3,4,5,6,7,8,9,10,11},{0,1,3,4,5,6,7,8,9,10,11},{0,1,2,4,5,6,7,8,9,10,11},{0,1,2,3,5,6,7,8,9,10,11},{0,1,2,3,4,6,7,8,9,10,11},{0,1,2,3,4,5,7,8,9,10,11},{0,1,2,3,4,5,6,8,9,10,11},{0,1,2,3,4,5,6,7,9,10,11},{0,1,2,3,4,5,6,7,8,10,11},{0,1,2,3,4,5,6,7,8,9,11},{0,1,2,3,4,5,6,7,8,9,10}};
//    expectAns = 11;
//    TEST_SMP1(Solution, shortestPathLength, expectAns, first);

    first  = {{2,3},{7},{0,6},{0,4,7},{3,8},{7},{2},{5,3,1},{4}};
    expectAns = 11;
    TEST_SMP1(Solution, shortestPathLength, expectAns, first);

    return 0;
}
