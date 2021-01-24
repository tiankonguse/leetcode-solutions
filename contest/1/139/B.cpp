/*************************************************************************
    > File Name: flip-columns-for-maximum-number-of-equal-rows.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  2 10:24:26 2019
    > link: https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/
    > No: 1072. Flip Columns For Maximum Number of Equal Rows
    > Contest: https://leetcode.com/contest/weekly-contest-139
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    string vecToString(vector<int>& vec, int flag ){
        string tmp;
        for(auto v: vec){
            tmp.push_back(flag?!v:v);
        }
        return tmp;
    }
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        map<string, string> mToFlip;
        map<string, int> mToNum;

        for(int i=0;i<matrix.size();i++){
            string tmp = vecToString(matrix[i], 0);
            if(mToFlip.find(tmp) == mToFlip.end()){
                mToFlip[tmp] = vecToString(matrix[i], 1);
            }
            mToNum[tmp]++;
        }

        int ans = 1;

        for(auto& p : mToNum){
            int tmp = p.second;
            auto& flip = mToFlip[p.first];
            if(mToNum.find(flip) != mToNum.end()){
                tmp += mToNum[flip];
            }
            ans = max(ans, tmp);
        }

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
