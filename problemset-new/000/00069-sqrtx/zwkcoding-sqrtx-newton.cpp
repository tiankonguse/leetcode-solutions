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
        double ans = x;
        double delta = 0.0001;
        while(fabs(pow(ans, 2) - x) > delta)  {
            // x_quota = x  + p = x + (-c(x) / c_quota(x))
            ans = (ans + x / ans) / 2;
        }
        return ans;
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
