/*************************************************************************
    > File Name: first-unique-character-in-a-string.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr 23 23:29:51 2019
    > link: https://leetcode.com/problems/first-unique-character-in-a-string/
    > No: 387. First Unique Character in a String
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int firstUniqChar(string str) {
        map<char, int>m;
        for(int i=0;i<str.size();i++){
            m[str[i]]++;
        }
        for(int i=0;i<str.size();i++){
            if(m[str[i]] == 1){
                return i;
            }
        }
        return -1;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first)
    TEST_SMP2(Solution, smallestRepunitDivByK, expectAns, first, second);

    int first;
    int second;
    int expectAns;


    first = 1;
    second = "";
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    string first;
    int expectAns;

    first = "leetcode";
    expectAns = 0;
    TEST_SMP1(Solution, firstUniqChar, expectAns, first);

    first = "loveleetcode";
    expectAns = 2;
    TEST_SMP1(Solution, firstUniqChar, expectAns, first);

    return 0;
}
