/*************************************************************************
    > File Name: largest-values-from-labels.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  16 10:24:26 2019
    > link: https://leetcode.com/problems/largest-values-from-labels/
    > No: 1090. Largest Values From Labels
    > Contest: https://leetcode.com/contest/weekly-contest-141
 ************************************************************************/

#include "../../../include/base.h"


class Solution {

public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        vector<pair<int, int>> nodes;
        for(int i=0;i<values.size();i++){
            nodes.push_back(make_pair(-values[i], labels[i]));
        }
        sort(nodes.begin(), nodes.end());
        
        map<int, int> labelNum;
        
        int ans = 0;
        for(auto p: nodes){
            if(labelNum[p.second] < use_limit){
                ans -= p.first;
                labelNum[p.second]++;
                num_wanted--;
                if(num_wanted == 0)break;
            }
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
