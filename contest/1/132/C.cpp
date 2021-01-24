/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 14 10:19:00 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        vector<map<int, int> > maxtr;
        maxtr.resize(A.size());
        int ans = 2;
        for(int i=0;i<A.size();i++){
            set<int> have;
            auto& m_now = maxtr[i];
            for(int j=i-1;j>=0;j--){
                int val = A[i] - A[j];
                auto& m_pre = maxtr[j];

                if(have.find(val) != have.end())continue;
                have.insert(val);

                if(m_pre.find(val) == m_pre.end()){
                    m_now[val] = 2;
                }else{
                    m_now[val] = m_pre[val] + 1;
                    ans = max(ans, m_now[val]);
                }
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

    first = {3,6,9,12};
    expectAns = 4;
    TEST_SMP1(Solution, longestArithSeqLength, expectAns, first);

    first = {9,4,7,2,10};
    expectAns = 3;
    TEST_SMP1(Solution, longestArithSeqLength, expectAns, first);

    first = {20,1,15,3,10,5,8};
    expectAns = 4;
    TEST_SMP1(Solution, longestArithSeqLength, expectAns, first);

    return 0;
}
