/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 10:12:57 2019
    > Contest:
    > Title:
    > Link:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    void init(vector<int>& A, int len, int* left, int* right){
        int maxAns = 0;
        int nowAns = 0;
        for(int i=0;i<len;i++){
            left[i] = -1;
            nowAns += A[i];
        }
        left[len-1] = maxAns = nowAns;
        for(int i=len;i<A.size();i++){
            nowAns += A[i] - A[i-len];
            left[i] = maxAns = max(maxAns, nowAns);
        }

        nowAns = 0;
        for(int i=A.size()-1, j=len;j>0;j--,i--){
            right[i] = -1;
            nowAns += A[i];
        }
        right[A.size()-len] = maxAns = nowAns;
        for(int i=A.size()-len-1;i>=0;i--){
            nowAns += A[i] - A[i+len];
            right[i] = maxAns = max(maxAns, nowAns);
        }
    }
public:
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
        int left[2][1000];
        int right[2][1000];
        enum {LL = 0, MM = 1};

        init(A, L, left[LL], right[LL]);
        init(A, M, left[MM], right[MM]);

        int maxAns = 0;
        for(int i=L-1;i < A.size()-M;i++){
            //printf("L:M i=%d left=%d right=%d sum=%d\n", i, left[LL][i], right[MM][i+1], left[LL][i] + right[MM][i+1]);
            maxAns = max(maxAns, left[LL][i] + right[MM][i+1]);
        }
        for(int i=M-1;i<A.size()-L;i++){
            //printf("M:L i=%d left=%d right=%d sum=%d\n", i, left[MM][i], right[LL][i+1], left[MM][i] + right[LL][i+1]);
            maxAns = max(maxAns, left[MM][i] + right[LL][i+1]);
        }
        return maxAns;
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
    vector<int> param1;
    int param2;
    int param3;
    int expectAns;


    param1 = {0,6,5,2,2,5,1,9,4};
    param2 = 1;
    param3 = 2;
    expectAns = 20;
    TEST_SMP3(Solution, maxSumTwoNoOverlap, expectAns, param1, param2, param3);



    param1 = {3,8,1,3,2,1,8,9,0};
    param2 = 3;
    param3 = 2;
    expectAns = 29;
    TEST_SMP3(Solution, maxSumTwoNoOverlap, expectAns, param1, param2, param3);



    param1 = {2,1,5,6,0,9,5,0,3,8};
    param2 = 4;
    param3 = 3;
    expectAns = 31;
    TEST_SMP3(Solution, maxSumTwoNoOverlap, expectAns, param1, param2, param3);
    return 0;
}
