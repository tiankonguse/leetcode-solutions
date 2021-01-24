/*************************************************************************
    > File Name: clumsy-factorial.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 10 09:57:35 2019
    > desc: 1006. Clumsy Factorial
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();


class Solution {
public:
    int clumsy(int N) {
        if(N <= 2) {
            return N;
        }

        int sum = N * (N - 1) / (N - 2);
        N -= 3;

        while(N>0) {
            sum += N;
            N--;
            if(N == 1) {
                sum -= N ;
                N -= 1;
            }else if(N == 2) {
                sum -= N * (N - 1);
                N -= 2;

            } else{
                sum -= N * (N - 1) / (N - 2);
                N -= 3;
            }
        }
        return sum;
    }
};
template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& N, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.clumsy(N);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("N", N);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    int data;
    int expectAns;


    data = 4;
    expectAns = 7;
    test(expectAns, data);

    data = 10;
    expectAns = 12;
    test(expectAns, data);


//
//    data = {7,7,8,6,5,6,6};
//    K = 3;
//    expectAns = 83;
//    test(data, K, expectAns);
//
//
//    data = {69,39,79,78,16,6,36,97,79,27,14,31,4};
//    K = 2;
//    expectAns = 1957;
//    test(data, K, expectAns);



    return 0;
}
