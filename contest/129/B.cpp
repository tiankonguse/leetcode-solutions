/*************************************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 24 09:24:48 2019
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
    int smallestRepunitDivByK(int K) {
        int sum = 0;
        set<int> have;
        for(int i=1;;i++){
            sum = (sum * 10 + 1)%K;
            if(sum == 0){
                return i;
            }
            if(have.find(sum) != have.end()){
                return -1;
            }
            have.insert(sum);
        }
        return -1;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.smallestRepunitDivByK(firstData);

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
    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    test(expectAns, first);



    first = 2;
    expectAns = -1;
    test(expectAns, first);

    first = 3;
    expectAns = 3;
    test(expectAns, first);




    return 0;
}
