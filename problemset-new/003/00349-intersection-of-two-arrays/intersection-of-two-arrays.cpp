/*************************************************************************
    > File Name: intersection-of-two-arrays.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 18:29:23 2019
 ************************************************************************/

#include "../../include/base.h"

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

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<int> first;
    vector<int> second;
    vector<int> expectAns;

    first = {1,2,2,1};
    second = {2,2};
    expectAns = {2};
    TEST_SMP2(Solution, intersection, expectAns, first, second);

    first = {4,9,5};
    second = {9,4,9,8,4};
    expectAns = {9,4};
    TEST_SMP2(Solution, intersection, expectAns, first, second);

    return 0;
}
