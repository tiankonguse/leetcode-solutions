/*************************************************************************
    > File Name: reverse-string.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 25 22:10:19 2019
    > link: https://leetcode.com/problems/reverse-string/
    > No: 344. Reverse String
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    void reverseString(vector<char>& s, int start = -1, int end = -1) {
        if(start == -1) {
            start = 0, end = s.size() - 1;
        }
        if(start < end) {
            swap(s[start], s[end]);
            reverseString(s, start+1, end-1);
        }
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
