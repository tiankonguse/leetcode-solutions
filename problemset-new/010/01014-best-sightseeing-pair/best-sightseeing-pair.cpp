/*************************************************************************
    > File Name: best-sightseeing-pair.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 24 09:24:55 2019
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
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int ans = A[0] + A[1] + 0 - 1;
        int maxSum = A[0] + 0;

        for(int i=1;i<A.size();i++){
            ans = max(ans, maxSum + A[i] - i);
            maxSum = max(maxSum, A[i] + i);
        }
        return ans;

    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.maxScoreSightseeingPair(firstData);

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
    int expectAns;


    first = {8,1,5,2,6};
    expectAns = 11;
    test(expectAns, first);


    return 0;
}
