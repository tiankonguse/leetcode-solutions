/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 17 10:29:18 2019
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
    vector<int> have;
    vector<int> bit;
    //A(10, k)
    int fun_A_n_k(int n, int k){
        int sum = 1;
        while(k-->0){
            sum *= n--;
        }
        return sum;
    }
    int dfs(int pos, int preNum) {
        if(pos < 0) {
            return 1;
        }
        int val = bit[pos];
        int ans = 0;
        for(int i=0; i<val; i++) {
            if(have[i]) {
                continue;
            }
            if(i == 0 && pos + 1 == bit.size()){
                continue;
            }
            ans += fun_A_n_k(9-preNum, pos);
        }
        if(!have[val]) {
            have[val]++;
            ans += dfs(pos-1, preNum+1);
        }
        return ans;
    }
public:
    int numDupDigitsAtMostN(int N) {
        int tmpN = N;
        have.resize(10,0);

        int ans = 0;
        if(N == 1000000000){
            N--;
        }


        while(N>0) {
            bit.push_back(N%10);
            N /= 10;
        }

        for(int i=1;i<bit.size();i++){
            ans += 9 * fun_A_n_k(9,i-1);
        }
        ans += dfs(bit.size()-1, 0);
        return tmpN - ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.numDupDigitsAtMostN(firstData);

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
    expectAns = 0;
    test(expectAns, first);


    first = 9;
    expectAns = 0;
    test(expectAns, first);


    first = 10;
    expectAns = 0;
    test(expectAns, first);


    first = 11;
    expectAns = 1;
    test(expectAns, first);

    first = 20;
    expectAns = 1;
    test(expectAns, first);


    first = 100;
    expectAns = 10;
    test(expectAns, first);



    first = 99;
    expectAns = 9;
    test(expectAns, first);

    first = 1000;
    expectAns = 262;
    test(expectAns, first);


    first = 110;
    expectAns = 12;
    test(expectAns, first);


    first = 111;
    expectAns = 13;
    test(expectAns, first);
    return 0;
}

