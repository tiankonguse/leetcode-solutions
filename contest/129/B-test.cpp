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


int main() {
    int ans = -1;
    for(int i=1; i<=100000; i++) {
        Solution work;
        ans = max(ans, work.smallestRepunitDivByK(i));
        if(i % 2500 == 0) {
            printf("i=%d ans=%d\n",i, ans);

        }
    }
    printf("ans=%d\n", ans);

    return 0;
}
