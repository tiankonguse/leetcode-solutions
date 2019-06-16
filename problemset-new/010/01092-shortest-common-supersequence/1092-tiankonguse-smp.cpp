/*************************************************************************
    > File Name: shortest-common-supersequence.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  16 10:24:26 2019
    > link: https://leetcode.com/problems/shortest-common-supersequence/
    > No: 1092. Shortest Common Supersequence
    > Contest: https://leetcode.com/contest/weekly-contest-141
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    int commPath[1111][1111];
    void getCommPath(string& str1, string& str2){
        memset(commPath, 0, sizeof(commPath));
        for(int i=1;i<=str1.length();i++){
            for(int j=1;j<=str2.length();j++){
                if(str1[i-1] == str2[j-1]){
                    commPath[i][j] = commPath[i-1][j-1] + 1;
                }else{
                    commPath[i][j] = max(commPath[i-1][j], commPath[i][j-1]);
                }
            }
        }
    }
public:
    string shortestCommonSupersequence(string str1, string str2) {
        getCommPath(str1, str2);
        
        string ans;
        int x = str1.length();
        int y = str2.length();
        
        while(x > 0 &&  y > 0){
            if(str1[x-1] == str2[y-1]){
                ans.push_back(str1[x-1]);
                x--,y--;
                continue;
            }
            
            if(commPath[x][y] == commPath[x-1][y]){
                ans.push_back(str1[x-1]);
                x--;
            }else{
                ans.push_back(str2[y-1]);
                y--;
            }
        }
        
        while(y > 0){
            ans.push_back(str2[y-1]);
            y--;
        }
        while(x > 0){
            ans.push_back(str1[x-1]);
            x--;
        }
        
        
        std::reverse(ans.begin(),ans.end());
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
