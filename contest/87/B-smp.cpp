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
        vector<int>left;
        vector<int>right;
        int ans = 0;

        left.resize(A.size(), 0);
        for(int i=1; i<A.size(); i++) {
            if(A[i] > A[i-1]) {
                left[i] = left[i-1] + 1;
            }
        }

        right.resize(A.size(), 0);
        for(int i=A.size()-2; i>=0; i--) {
            if(A[i] > A[i+1]) {
                right[i] = right[i+1] + 1;
            }
        }
        for(int i=1; i<A.size()-1; i++) {
            if(left[i] > 0 && right[i] > 0) {
                ans = max(ans, left[i] + right[i] + 1);
            }
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
