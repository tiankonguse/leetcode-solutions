/*************************************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 24 09:24:48 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int smallestRepunitDivByK(int K) {
        int sum = 0;
        set<int> have;
        for(int i=1;;i++){
            sum = (sum * 10 + 1)%K;
            if(sum == 0){
                return i;
            }
            if(have.find(sum) != have.end()){
                return -1;
            }
            have.insert(sum);
        }
        return -1;
    }
};


int main() {
    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    first = 2;
    expectAns = -1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    first = 3;
    expectAns = 3;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    first = 113;
    expectAns = 112;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    first = 7;
    expectAns = 6;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);



    return 0;
}
