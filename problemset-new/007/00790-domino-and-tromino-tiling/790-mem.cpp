#include <bits/stdc++.h>

#include "base.h"
using namespace std;


int FULL = 0 ,UP1 =1, DOWN1 =2,  END =3;
int PRE = 0, CUR = 1, NEXT = 2;

typedef long long ll;
class Solution {
public:
    int numTilings(int n) {
        // 边界为 n 的状态:  充满 与 一个缺口
        vector<vector<ll>> dp(3, vector<ll>(END, 0));
        ll mod = 1000000007;
        dp[0][FULL] = 1;
        for(int i=1;i<=n;i++){

            // FULL
            dp[CUR][FULL] += dp[PRE][FULL]; // 1*2 竖着
            dp[NEXT][FULL] += dp[PRE][FULL];  // 1*2 两个横着
            dp[NEXT][UP1] += dp[PRE][FULL];
            dp[NEXT][DOWN1] += dp[PRE][FULL];


            // UP1, DOWN1
            dp[CUR][UP1] += dp[PRE][DOWN1];
            dp[CUR][FULL] += dp[PRE][DOWN1];

            dp[CUR][DOWN1] += dp[PRE][UP1];
            dp[CUR][FULL] += dp[PRE][UP1];

            
            for(int k=0;k<NEXT;k++){
                dp[k] = dp[k+1];
            }
            for(int k=0;k<END;k++){
                dp[PRE][k] %= mod;
                dp[NEXT][k] = 0;
            }
            
        }
        return dp[PRE][FULL] % mod;
    }
};