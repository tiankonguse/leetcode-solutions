#include <bits/stdc++.h>

#include "base.h"
using namespace std;


int FULL = 0 ,UP1 =1, DOWN1 =2,  END =3;

typedef long long ll;
class Solution {
public:
    int numTilings(int n) {
        // 边界为 n 的状态:  充满 与 一个缺口
        vector<vector<ll>> dp(n+3, vector<ll>(END, 0));
        ll mod = 1000000007;
        dp[0][FULL] = 1;
        for(int i=1;i<=n;i++){

            // FULL
            dp[i][FULL] += dp[i-1][FULL]; // 1*2 竖着
            dp[i+1][FULL] += dp[i-1][FULL];  // 1*2 两个横着
            dp[i+1][UP1] += dp[i-1][FULL];
            dp[i+1][DOWN1] += dp[i-1][FULL];


            // UP1, DOWN1
            dp[i][UP1] += dp[i-1][DOWN1];
            dp[i][FULL] += dp[i-1][DOWN1];

            dp[i][DOWN1] += dp[i-1][UP1];
            dp[i][FULL] += dp[i-1][UP1];

            
            for(int k=0;k<END;k++){
                dp[i][k] %= mod;
                dp[i+1][k] %= mod;
            }

        }
        return dp[n][FULL] % mod;
    }
};