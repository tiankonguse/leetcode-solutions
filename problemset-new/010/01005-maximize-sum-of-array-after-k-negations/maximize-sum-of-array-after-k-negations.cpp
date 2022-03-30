/*************************************************************************
    > File Name: maximize-sum-of-array-after-k-negations.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 10 09:57:23 2019
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
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        for(int i=0;i<A.size() && K > 0;i++){
            if(A[i] < 0){
                K--;
                A[i] = -A[i];
            }else{
                break;
            }
        }
        if(K > 0){
            sort(A.begin(), A.end());
            if(K%2 == 1){
                A[0] = -A[0];
            }
        }
        int sum = 0;
        for(int i=0;i<A.size();i++){
            sum += A[i];
        }
        return sum;
    }
};
template <class ansType, class dataType1 = int, class dataType2 = int>
void test(ansType& expectAns, dataType1& A = dataType1(), dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.largestSumAfterKNegations(A, K);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("A", A);
        output("K", K);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<int> data;
    int K;
    int expectAns;


    data = {4,2,3};
    K = 1;
    expectAns = 5;
    test(expectAns, data, K);



    data = {3,-1,0,2};
    K = 3;
    expectAns = 6;
    test(expectAns, data, K);




    data = {2,-3,-1,5,-4};
    K = 2;
    expectAns = 13;
    test(expectAns, data, K);
    return 0;
}

