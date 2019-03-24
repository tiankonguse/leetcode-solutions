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
    int ans = -1;

    double startTime = getCurrentTime();
    Solution work;
    for(int i=1; i<=100000; i++) {
        ans = max(ans, work.smallestRepunitDivByK(i));
        if(i % 2500 == 0) {
            double useTime = (getCurrentTime() - startTime)/1000;
            printf("i=%d ans=%d use %.3lfs\n",i, ans, useTime);
            startTime = getCurrentTime();
        }
    }
    printf("ans=%d\n", ans);

    return 0;
}
