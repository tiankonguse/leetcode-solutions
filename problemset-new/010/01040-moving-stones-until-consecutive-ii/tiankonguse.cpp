/*************************************************************************
    > File Name: moving-stones-until-consecutive-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月 7日  9:50:42
    > No: 1040. Moving Stones Until Consecutive II
    > Contest: 135
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int len;
    int maxStep;

    int findLeft(vector<int>& str, int leftVal) {
        int left = 0;
        int right = str.size();
        int mid;
        while(left < right) {
            mid = (left + right)/2;
            if(str[mid] <= leftVal) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left - 1;
    }

    int findRight(vector<int>& str, int rightVal) {
        int left = 0;
        int right = str.size();
        int mid;
        while(left < right) {
            mid = (left + right)/2;
            if(str[mid] < rightVal) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return right;

    }

    int findMinStep(vector<int>& str, int leftVal) {
        int rightVal = leftVal+len-1;
        if(leftVal < str[0] || rightVal > str[len-1]) {
            return maxStep;
        }
        //确定左右边界是否可以形成
        int leftPos = findLeft(str, leftVal); // <= leftVal
        int rightPos = findRight(str, rightVal); // >= rightVal

        if(str[leftPos] == leftVal && str[rightPos] == rightVal) {
            return leftPos + len -1 - rightPos;
        }

        if(leftPos == 0 && rightPos == len -1) {
            //no way
            return maxStep;
        }

        if(str[leftPos] == leftVal || str[rightPos] == rightVal) {
            return leftPos + (len -1 - rightPos) + 1;
        } else {
            return leftPos + (len -1 - rightPos) + 2;
        }
    }

public:
    vector<int> numMovesStonesII(vector<int>& str) {
        sort(str.begin(), str.end());
        len = str.size();
        maxStep = (str[len-1] - str[0] + 1) - len - (min(str[1]-str[0], str[len-1] - str[len-2]) - 1);
        int minStep = maxStep;
        for(int i=0; i<str.size(); i++) {
            for(int j = -2; j<=2; j++) {
                minStep = min(minStep, findMinStep(str, str[i] + j));
            }
        }
        return {minStep, maxStep};
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
#define FUNCTION numMovesStonesII

    vector<int> first;
    vector<int> expectAns;

    first = {7,4,9};
    expectAns = {1,2};
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {6,5,4,3,10};
    expectAns = {2,3};
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {100,101,104,102,103};
    expectAns = {0,0};
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);


    return 0;
}
