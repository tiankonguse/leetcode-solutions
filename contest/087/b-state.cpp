/*****************
********************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月28日 18:28:44
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int longestMountain(vector<int>& A) {
        if(A.size() < 3){
            return 0;
        }
        int first = 0, mid = -1, ans = 0;
        int state = 0; //0:up, 1:mid 2:down
        for(int i=1;i<A.size();i++){
            if(state == 0){
                if(A[i] > A[i-1]){
                    state =1;
                    mid = i;
                    continue;
                }
            }else if(state ==1){
                 if(A[i] > A[i-1]){
                    mid = i;
                    continue;
                }else if(A[i] < A[i-1]){
                    state = 2;
                    ans = max(ans, i - first + 1);
                    continue;
                }
            }else{
                if(A[i] < A[i-1]){
                    ans = max(ans, i - first + 1);
                    continue;
                }else if(A[i] > A[i-1]){
                    state = 1;
                    first = i - 1;
                    mid = i;
                    continue;
                }
            }

            state = 0;
            first = i;
            mid = -1;
        }
        return ans;
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
    vector<int> first;
    int expectAns;

    first = {2,1,4,7,3,2,5};
    expectAns = 5;
    TEST_SMP1(Solution, longestMountain, expectAns, first);

    first = {2,2,2};
    expectAns = 0;
    TEST_SMP1(Solution, longestMountain, expectAns, first);

    return 0;
}
