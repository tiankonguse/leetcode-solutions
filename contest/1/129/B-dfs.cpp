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
    vector<vector<vector<int>>> numMap;
public:
    Solution() {
        numMap.resize(10);
        for(int i=0; i<numMap.size(); i++) {
            numMap[i].resize(10);
        }
        for(int i=0; i<=9; i++) {
            for(int j=0; j<=9; j++) {
                int ij = (i*j)% 10;
                numMap[i][ij].push_back(j);
            }
        }
    }
    bool check(long long sum) {
        while(sum>0) {
            if(sum%10 != 1) {
                return false;
            }
            sum /= 10;
        }
        return true;
    }
    int smallestRepunitDivByK(int K) {
        int pos = 0;
        long long sum = 0;
        int ans = 1;
        while(1) {
            int expNum = (11 - (sum%10)) % 10;
            vector<int>& numSet = numMap[K%10][expNum];
            if(numSet.size() == 0) {
                return -1;
            }
            sum += numSet[0] * K;
            sum /= 10;
            if(sum == 0) {
                return ans;
            }
            ans++;
        }
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

    first = 7;
    expectAns = 6;
    test(expectAns, first);

    first = 1;
    expectAns = 1;
    test(expectAns, first);



    first = 2;
    expectAns = -1;
    test(expectAns, first);

    first = 3;
    expectAns = 3;
    test(expectAns, first);


    first = 3;
    expectAns = 3;
    test(expectAns, first);


    first = 112;
    expectAns = -1;
    test(expectAns, first);

    first = 116;
    expectAns = -1;
    test(expectAns, first);




    first = 3;
    expectAns = 3;
    test(expectAns, first);

    for(int i=113; i<=100000; i++) {
        if(i%2==0 || i%5==0)
            continue;
        Solution work;
        int ans = work.smallestRepunitDivByK(i);
        printf("i=%d ans=%d\n",i, ans);
    }

    return 0;
}
