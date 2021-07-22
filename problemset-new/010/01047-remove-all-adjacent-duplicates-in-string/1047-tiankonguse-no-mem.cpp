/*************************************************************************
    > File Name: remove-all-adjacent-duplicates-in-string.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 19 10:27:35 2019
    > link: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
    > No: 1047. Remove All Adjacent Duplicates In String
    > Contest: https://leetcode.com/contest/weekly-contest-137
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    string removeDuplicates(string& s) {
        int n = s.length();
        int l = 1, r = 1;
        while(r < n) {
            if(l > 0 && s[l-1] == s[r]) {
                l--,r++;
            }else{
                s[l++] = s[r++];
            }
        }
        s.resize(l);
        return s;
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
#define FUNCTION removeDuplicates

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
