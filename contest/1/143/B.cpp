/*************************************************************************
    > File Name: path-in-zigzag-labelled-binary-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2019年06月30日 11:37:47
    > link:
    > No: 1104. Path In Zigzag Labelled Binary Tree
    > Contest: https://leetcode.com/contest/weekly-contest-143
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<pair<int, int>> tree;
        tree.push_back({1,1});
        int deep = 1;
        int sum = 1;
        int num = 1;
        while(sum < label){
            deep++;
            num = num * 2;
            tree.push_back({sum+1, sum+num});
            sum += num;
        }
        vector<int> ans;
        int realPos = 0;
        int dir = deep%2;
        if(dir == 1){
            realPos = label;
        }else{
            realPos = tree.back().second - (label - tree.back().first);
        }
        ans.push_back(label);
        deep--;
        realPos = realPos/2;
        tree.pop_back();
        
        while(deep > 0){
            if(deep%2 == 1){
                ans.push_back(realPos);
            }else{
                ans.push_back(tree.back().second - (realPos - tree.back().first));
            }
            realPos = realPos/2;
            deep--;
            tree.pop_back();
        }
        sort(ans.begin(), ans.end());
        
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
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
