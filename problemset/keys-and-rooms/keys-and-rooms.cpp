/*************************************************************************
    > File Name: keys-and-rooms.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr  9 22:55:32 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        stack<int> sta;
        vector<int> have(rooms.size(), 0);
        int ans=1;
        sta.push(0);
        have[0]=1;

        while(!sta.empty()){
            auto pos = sta.top();
            sta.pop();

            auto& v = rooms[pos];
            for(int i=0;i<v.size();i++){
                if(have[v[i]])continue;
                ans++;
                sta.push(v[i]);
                have[v[i]]=1;
            }
        }

        return ans == rooms.size();
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
    bool expectAns;

    first = {{1},{2},{3},{}};
    expectAns = true;
    TEST_SMP1(Solution, canVisitAllRooms, expectAns, first);

    first = {{1,3},{3,0,1},{2},{0}};
    expectAns = false;
    TEST_SMP1(Solution, canVisitAllRooms, expectAns, first);

    return 0;
}
