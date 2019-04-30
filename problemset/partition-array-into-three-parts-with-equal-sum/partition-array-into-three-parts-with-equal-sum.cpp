/*************************************************************************
    > File Name: partition-array-into-three-parts-with-equal-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 24 09:24:33 2019
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

typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();

class Solution {
    const int debug = 0;
    int findSum(vector<int>& A, int start, int minsum){
        int sum = 0;
        for(int i=start;i<A.size();i++){
            sum += A[i];
            if(sum == minsum){
                return i;
            }
        }
        return -1;
    }
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int sum = 0;
        for(int i=0;i<A.size();i++){
            sum += A[i];
        }
        if(sum%3 !=0){
            return false;
        }

        int minsum = sum /3;

        int firstPos = findSum(A, 0, minsum);
        if(firstPos == -1){
            return false;
        }

        int secondPos = findSum(A, firstPos+1, minsum);
        if(secondPos == -1){
            return false;
        }

        return true;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.canThreePartsEqualSum(firstData);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("firstData", firstData);
        output("secondData", secondData);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<int> first;
    bool expectAns;


    first = {0,2,1,-6,6,-7,9,1,2,0,1};
    expectAns = true;
    test(expectAns, first);


    first = {0,2,1,-6,6,7,9,-1,2,0,1};
    expectAns = false;
    test(expectAns, first);



    first = {3,3,6,5,-2,2,5,1,-9,4};
    expectAns = true;
    test(expectAns, first);

    return 0;
}
