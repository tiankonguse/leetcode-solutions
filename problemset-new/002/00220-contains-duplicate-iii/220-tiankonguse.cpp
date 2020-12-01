/*************************************************************************
    > File Name: contains-duplicate-iii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 01:43:05 2019
    > link: https://leetcode.com/problems/contains-duplicate-iii/
    > No: 220. Contains Duplicate III
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        multiset<long long> s;
        for(int i=0, j = 0; i<nums.size(); i++) {
            if(i-j > k) {
                s.erase(nums[j]);
                j++;
            }
            s.insert(nums[i]);
            auto it = s.find(nums[i]);
            if(it != s.begin()) { //not min
                it--;
                if(nums[i] - *it <= t) {
                    printf("i=%d j=%d now=%d <= it=%d\n", i, j, nums[i], *it);
                    return true;
                }
                it++;
            }
            it++;
            if(it != s.end()) {
                if(*it - nums[i] <= t) {
                    printf("i=%d j=%d now=%d >= it=%d\n", i, j, nums[i], *it);
                    return true;
                }
            }
        }
        return false;
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
