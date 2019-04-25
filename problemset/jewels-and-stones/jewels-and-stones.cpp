/*************************************************************************
    > File Name: jewels-and-stones.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 22:50:45 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int numJewelsInStones(string base, string str) {
        set<char>s(base.begin(),base.end());
        int ans = 0;
        for(int i=0;i<str.size();i++){
            if(s.find(str[i]) != s.end()){
                ans++;
            }
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;


    first = 1;
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
*/
int main() {
    #define CLASS Solution
    #define FUNCTION numJewelsInStones

    string first;
    string second;
    int expectAns;

    first = "aA";
    second = "aAAbbbb";
    expectAns = 3;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = "z";
    second = "ZZ";
    expectAns = 0;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
