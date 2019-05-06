/*
 * Filename: /home/zwk/code/data_structrue/c++/binary_search/sqrtx/main.cpp
 * Path: /home/zwk/code/data_structrue/c++/binary_search/sqrtx
 * Created Date: Sunday, May 5th 2019, 9:29:43 pm
 * Author: zwk
 * 
 * Copyright (c) 2019 Your Company
 */

#include "../../include/base.h"

class Solution {
public:
    int mySqrt(int x)
    {
        int left = 0;
        int right = x;
        int ans = 0;
        if (1 == x) {
            return 1;
        } else if (0 == x) {
            return 0;
        } else {
            // upper bound of binary search: ans <= x /ans
            while (left <= right) {
                int mid = left + ((right - left) >> 1);
                if (mid > x / mid) {
                    right = mid;
                } else {
                    if ((mid == x - 1) || (mid + 1) > (x / (mid + 1))) {
                        return mid;
                    } else {
                        left = mid + 1;
                    }
                }
            }
            return ans;
        }
    }
};

int main() {
    #define CLASS Solution
    #define FUNCTION mySqrt

    int first;
    int second;
    int expectAns;

    first = 4;
    expectAns = 2;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = 8;
    expectAns = 2;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = 16;
    expectAns = 4 ;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = 20;
    expectAns = 4;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
