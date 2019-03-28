/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月28日 18:28:40
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    string fix(string& str) {
        char buf[222];
        int len = 0;
        for(int i=0; i<str.length(); i++) {
            if(str[i] == '#') {
                if(len >0) {
                    len--;
                }
            } else {
                buf[len++] = str[i];
            }
        }
        buf[len] = '\0';
        return buf;
    }
public:
    bool backspaceCompare(string S, string T) {
        return fix(S) == fix(T);
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
    string second;
    bool expectAns;

    first = "ab#c";
    second =  "ad#c";
    expectAns = 1;
    TEST_SMP2(Solution, backspaceCompare, expectAns, first, second);


    first = "ab##";
    second =  "c#d#";
    expectAns = 1;
    TEST_SMP2(Solution, backspaceCompare, expectAns, first, second);



    first = "a##c";
    second =  "#a#c";
    expectAns = 1;
    TEST_SMP2(Solution, backspaceCompare, expectAns, first, second);


    first = "a#c";
    second =  "b";
    expectAns = 0;
    TEST_SMP2(Solution, backspaceCompare, expectAns, first, second);



    return 0;
}
