/*************************************************************************
    > File Name: tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon May 27 22:52:03 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> s(nums1.begin(), nums1.end());
        vector<int>  ans;
        for(int i=0; i<nums2.size(); i++) {
            if(s.find(nums2[i]) != s.end()) {
                ans.push_back(nums2[i]);
                s.erase(nums2[i]);
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
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
