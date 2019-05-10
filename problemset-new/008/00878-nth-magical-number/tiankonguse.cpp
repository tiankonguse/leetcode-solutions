/*************************************************************************
    > File Name: nth-magical-number.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月10日 17:05:56
    > link: https://leetcode.com/problems/nth-magical-number/
    > No: 878. Nth Magical Number
    > Contest: 95
 ************************************************************************/

#include "../../include/base.h"


typedef long long LL;
class Solution {
    LL gcd(LL a, LL b) {
        if(b == 0)
            return a;
        else
            return gcd(b, a % b);
    }
    LL findIndex(LL A, LL B, LL loopIndex) {
        LL aNum = 0, bNum = 0;
        while(1) {
            if(loopIndex == 0) {
                return min(aNum, bNum);
            }
            if(aNum < bNum) {
                aNum += A;
            } else if(aNum > bNum) {
                bNum += B;
            } else {
                aNum += A;
                bNum += B;
            }
            loopIndex--;
        }

    }
public:
    int nthMagicalNumber(int N, int A, int B) {
        LL mod = 1000000007;
        LL minGcd = gcd(A, B);
        LL maxGcd = A/minGcd * B;
        LL loop = maxGcd/A + maxGcd/B - 1;

        LL loopNum = N /loop;
        LL loopIndex = N % loop;

        LL indexVal = findIndex(A, B, loopIndex);

        LL ans = (loopNum * maxGcd) % mod;
        ans = (ans + indexVal) % mod;
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
#define FUNCTION nthMagicalNumber

    int first;
    int second;
    int third;
    int expectAns;

    first = 1;
    second = 2;
    third = 3;
    expectAns = 2;
    TEST_SMP3(CLASS, FUNCTION, expectAns, first, second, third);

    return 0;
}
