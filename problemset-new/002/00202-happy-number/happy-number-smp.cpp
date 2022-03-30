/*************************************************************************
    > File Name: happy-number-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 18:47:11 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
   int happy(int n){
        int ans = 0;
        while(n){
            ans += (n % 10) * (n % 10);
            n = n / 10;
        }
        return ans;
    }
public:
    bool isHappy(int n) {
        set<int> s;
        while(s.find(n) == s.end()){
            s.insert(n);
            n = happy(n);
            if(n == 1){
                return true;
            }
        }
        return false;
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
    int first;
    bool expectAns;

    first = 19;
    expectAns = true;
    TEST_SMP1(Solution, isHappy, expectAns, first);

    return 0;
}

