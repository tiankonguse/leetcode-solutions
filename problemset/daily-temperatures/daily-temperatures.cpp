/*************************************************************************
    > File Name: daily-temperatures.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr  2 23:55:24 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> sta;
        vector<int> ans;
        ans.resize(T.size(), 0);
        for(int i=0;i<T.size();i++){
            while(!sta.empty() && T[sta.top()] < T[i]){
                ans[sta.top()] = i - sta.top();
                sta.pop();
            }
            sta.push(i);
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
    vector<int> expectAns;

    first = {73, 74, 75, 71, 69, 72, 76, 73};
    expectAns = {1, 1, 4, 2, 1, 1, 0, 0};
    TEST_SMP1(Solution, dailyTemperatures, expectAns, first);


    return 0;
}
