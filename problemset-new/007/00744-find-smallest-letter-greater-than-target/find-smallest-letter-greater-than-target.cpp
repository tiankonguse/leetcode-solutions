/*************************************************************************
    > File Name: find-smallest-letter-greater-than-target.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 22:39:40 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0, right = letters.size(), mid;
        while(left < right){
            mid = (left + right)/2;
            if(letters[mid] <= target){
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        if(left == letters.size()){
            left = 0;
        }
        return letters[left];
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
    #define CLASS Solution
    #define FUNCTION nextGreatestLetter

    vector<char> first;
    char second;
    char expectAns;

    first = {'c', 'f', 'j'};
    second = 'a';
    expectAns = 'c';
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {'c', 'f', 'j'};
    second = 'c';
    expectAns = 'f';
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = {'c', 'f', 'j'};
    second = 'd';
    expectAns = 'f';
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = {'c', 'f', 'j'};
    second = 'g';
    expectAns = 'j';
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {'c', 'f', 'j'};
    second = 'j';
    expectAns = 'c';
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {'c', 'f', 'j'};
    second = 'k';
    expectAns = 'c';
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
