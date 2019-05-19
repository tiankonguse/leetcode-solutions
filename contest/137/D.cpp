/*************************************************************************
    > File Name: last-stone-weight-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 19 10:27:35 2019
    > link: https://leetcode.com/problems/last-stone-weight-ii/
    > No: 1049. Last Stone Weight II
    > Contest: https://leetcode.com/contest/weekly-contest-137
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        set<int> s;
        s.insert(0);
        int sum = accumulate(stones.begin(),stones.end(),0)/2;
        for(auto stone : stones){
            set<int> tmp;
            for(auto& val : s){
                if(val <= sum){
                    tmp.insert(stone + val);
                }
                if(val >= -sum){
                    tmp.insert(stone - val);
                }
            }
            s.swap(tmp);
        }
        int ans = abs(*s.begin());
        for(auto& val : s){
            ans = min(ans, abs(val));
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION lastStoneWeightII

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
