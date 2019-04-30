/*************************************************************************
    > File Name: powx-n.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 21:43:09 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) {
            return 1;
        }
        double ans = 1;
        double base = x;
        long long lev = n;
        if(lev<0) {
            lev = -lev;
            base = 1/x;
        }
        while(lev) {
            if(lev&1) {
                ans *= base;
            }
            base = base * base;
            lev = lev /2;
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
#define CLASS Solution
#define FUNCTION myPow

    double first;
    int second;
    double expectAns;

    first = 2.00000;
    second = 10;
    expectAns = 1024.00000;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = 2.10000;
    second = 3;
    expectAns = 9.26100;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = 2.00000;
    second = -2;
    expectAns = 0.25000;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
