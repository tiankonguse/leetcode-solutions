/*************************************************************************
    > File Name: first-bad-version-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 11:11:17 2019
    > link: https://leetcode.com/problems/first-bad-version
    > No: 278. First Bad Version
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

// Forward declaration of isBadVersion API.
int badVersion;
bool isBadVersion(int version) {
    return version >= badVersion;
}

class Solution {
public:
    int firstBadVersion(int n) {
        long long left=1, right=n, mid;
        while(left < right) {
            mid = (left + right)/2;
            if(!isBadVersion(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
*/
int main() {
#define CLASS Solution
#define FUNCTION firstBadVersion

    int first;
    int expectAns;

    first = 5;
    badVersion = 4;
    expectAns = 4;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
