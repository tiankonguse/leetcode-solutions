/*************************************************************************
    > File Name: reverse-words-in-a-string-iii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  1 02:32:03 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    string reverseWords(string s) {
        auto start = s.begin();
        for(auto it = s.begin(); it != s.end(); ) {
            while(it != s.end() && *it != ' ') {
                it++;
            }
            std::reverse(start,it);
            if(it == s.end())
                break;
            it++;//skip space
            start = it;
        }
        return s;
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
    string first;
    string expectAns;

    first = "Let's take LeetCode contest";
    expectAns = "s'teL ekat edoCteeL tsetnoc";
    TEST_SMP1(Solution, reverseWords, expectAns, first);

    return 0;
}
