/*************************************************************************
    > File Name: adding-two-negabinary-numbers.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  2 10:24:26 2019
    > link: https://leetcode.com/problems/adding-two-negabinary-numbers/
    > No: 1073. Adding Two Negabinary Numbers
    > Contest: https://leetcode.com/contest/weekly-contest-139
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        std::reverse(arr1.begin(), arr1.end());
        std::reverse(arr2.begin(), arr2.end());

        int maxSize = 1 + max(arr1.size(), arr2.size())*2;
        vector<int> ans(maxSize, 0);

        arr1.resize(maxSize, 0);
        arr2.resize(maxSize, 0);

        for(int i=0;i<ans.size();i++){
            ans[i] = arr1[i] + arr2[i];
        }

        for(int i=0;i<ans.size();i++){
            while(ans[i] >= 2 && ans[i+1] > 0){
                ans[i] -= 2;
                ans[i+1]--;
            }
            if(ans[i] >= 2){
                ans[i] -= 2;
                ans[i+1]++;
                ans[i+2]++;
            }
        }
        int lastPos = ans.size() - 1;
        while(lastPos>0 && ans[lastPos] == 0){
            lastPos--;
        }
        ans.resize(lastPos+1);
        std::reverse(ans.begin(), ans.end());
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
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
