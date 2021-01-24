/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 14 10:19:00 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    vector<int> have;

    bool dfs(int n){
        if(have[n] != -1){
            return have[n];
        }
        int ans = 0;
        for(int i=1;i<n;i++){
            if(n%i==0 && dfs(n-i) == 0){
                ans = 1;
                break;
            }
        }
        return have[n] = ans;
    }

public:
    bool divisorGame(int N) {
        have.resize(N+1, -1);
        have[1] = 0;
        return dfs(N);
    }
};

/*
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

    first = 2;
    expectAns = true;
    TEST_SMP1(Solution, divisorGame, expectAns, first);

    first = 3;
    expectAns = false;
    TEST_SMP1(Solution, divisorGame, expectAns, first);

    return 0;
}
