/*************************************************************************
    > File Name: minimum-cost-to-merge-stones.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri Mar  8 23:50:50 2019
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
    vector<vector<int>> dp;
    vector<int> prefixSum; //prefixSum[i] = sum(0,...,i-1)
    vector<int> stones;
    int K;

    int dfs(const int left, const int right) {//dfs[left, right]只有，个数小于K
        if(dp[left][right] != -1) {
            return dp[left][right];
        }
        int num = right - left + 1;
        int after  = 1 + (num - 1) % (K - 1);
        int sumK =  prefixSum[right+1] - prefixSum[left];
        if(num < K) {
            return dp[left][right] = 0;
        }else if(num == K) {
            return dp[left][right] = sumK;
        }

        int sum =0;
        for(int i=left; i<right; i+=K-1) {
            if(after == 1) {
                sum = dfs(left, i) + dfs(i+1, right) + sumK;
            } else {
                sum = dfs(left, i) + dfs(i+1, right);
            }

            if(dp[left][right] == -1) {
                dp[left][right] = sum;
            } else {
                dp[left][right] = min(dp[left][right], sum);
            }
        }
        return dp[left][right];
    }
public:
    int mergeStones(vector<int> stones, int K) {
        //if has ans
        if((stones.size() - 1) % (K - 1) != 0) {
            return -1;
        }
        int n = stones.size();
        //init
        prefixSum.resize(n+1, 0);
        dp.resize(n, vector<int>(n, -1));
        for(int i=0; i< n; i++) { //prefixSum[i] = sum(0,...,i-1)
            prefixSum[i+1] = prefixSum[i] + stones[i];
        }

        this->stones.swap(stones);
        this->K = K;
        //dfs(0, n - 1);
        //output("prefixSum", prefixSum);
        //output("dp", dp);
        return dfs(0, n - 1);
    }
};
template <class ansType, class dataType1, class dataType2>
void test(dataType1& stones, dataType2 K, ansType& expectAns) {
    Solution work;
    ansType ans;
    ans = work.mergeStones(stones, K);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("stones", stones);
        output("K", K);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<int> data;
    int K;
    int expectAns;


    data = {3,2,4,1};
    K = 3;
    expectAns = -1;
    test(data, K, expectAns);


    data = {3,5,1,2,6};
    K = 3;
    expectAns = 25;
    test(data, K, expectAns);


    data = {6,4,4,6};
    K = 2;
    expectAns = 40;
    test(data, K, expectAns);


    data = {3,2,4,1};
    K = 2;
    expectAns = 21;
    test(data, K, expectAns);


//
//    data = {7,7,8,6,5,6,6};
//    K = 3;
//    expectAns = 83;
//    test(data, K, expectAns);
//
//
//    data = {69,39,79,78,16,6,36,97,79,27,14,31,4};
//    K = 2;
//    expectAns = 1957;
//    test(data, K, expectAns);



    return 0;
}

