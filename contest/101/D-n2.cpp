/*************************************************************************
    > File Name: D.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月15日 16:43:01
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
    int numPermsDISequence(string S) {
        const int n = S.size() + 1;
        const int mod = 1000000007;
        //dp[i][j]: 0~i这些数字以j为后缀的排列个数
        int dp[n+1][n+1];
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;
        for(int i=1; i<n; i++) {
            if(S[i-1] == 'D') {
                int sum = 0;
                for(int j=i; j>=0; j--){
                    sum = (sum + dp[i-1][j]) % mod;
                    dp[i][j] = (dp[i][j] + sum) % mod;
                }
            } else {
                int sum = 0;
                for(int j=0;j<=i;j++){
                    dp[i][j] = (dp[i][j] + sum) % mod;
                    sum = (sum + dp[i-1][j]) % mod;
                }
            }
        }
        int ans = 0;
        for(int i=0; i<n; i++) {
            ans = (ans + dp[n-1][i]) % mod;
        }

        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.numPermsDISequence(firstData);

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
    string first;
    int expectAns;


    first = "DID";
    expectAns = 5;
    test(expectAns, first);



    return 0;
}

