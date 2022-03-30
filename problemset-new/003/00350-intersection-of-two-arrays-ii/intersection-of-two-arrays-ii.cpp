/*************************************************************************
    > File Name: intersection-of-two-arrays-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr 23 23:42:14 2019
    > link: https://leetcode.com/problems/intersection-of-two-arrays-ii/
    > No: 350. Intersection of Two Arrays II
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map<int, int>m;
        for(int i=0;i<nums1.size();i++){
            m[nums1[i]]++;
        }
        vector<int>ans;
        for(int i=0;i<nums2.size();i++){
            if(m[nums2[i]] > 0){
                ans.push_back(nums2[i]);
                m[nums2[i]]--;
            }
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define FUN smallestRepunitDivByK

    TEST_SMP1(Solution, FUN, expectAns, first)
    TEST_SMP2(Solution, FUN, expectAns, first, second);

    int first;
    int second;
    int expectAns;


    first = 1;
    second = "";
    expectAns = 1;
    TEST_SMP1(Solution, FUN, expectAns, first);
*/
int main() {
    #define CLASS Solution
    #define FUNCTION intersect

    vector<int> first;
    vector<int> second;
    vector<int> expectAns;

    first = {1,2,2,1};
    second = {2,2};
    expectAns = {2,2};
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {4,9,5};
    second = {9,4,9,8,4};
    expectAns = {4,9};
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
