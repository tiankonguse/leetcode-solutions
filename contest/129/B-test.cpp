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
#include <sys/time.h>

#include<windows.h>
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

typedef unsigned uint;
typedef unsigned char uchar;


class Solution {
public:
    int smallestRepunitDivByK(int K) {
        int sum = 0;
        set<int> have;
        for(int i=1;; i++) {
            sum = (sum * 10 + 1)%K;
            if(sum == 0) {
                return i;
            }
            if(have.find(sum) != have.end()) {
                return -1;
            }
            have.insert(sum);
        }
        return -1;
    }
};


double getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
int main() {
    int maxAns = -1;
    int maxPos = -1;

    double startTime = getCurrentTime();
    Solution work;
    for(int i=1; i<=100000; i++) {
        int ans = work.smallestRepunitDivByK(i);
        if(ans >= maxAns) {
            maxAns = ans;
            maxPos = i;
        }
        if(i % 2500 == 1) {
            double useTime = (getCurrentTime() - startTime)/1000;
            printf("maxPos=%5d maxAns=%5d pos=%5d ans=%5d  use %.3lfs\n",maxPos, maxAns,i, ans,  useTime);
            startTime = getCurrentTime();
        }
    }

    return 0;
}
