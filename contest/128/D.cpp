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
    //10^k
    int fun_base_10_k(int k){
        int sum = 1;
        while(k-->0){
            sum *= 10;
        }
        return sum;

    }
    //A(10, k)
    int fun_A_n_k(int n, int k){
        int sum = 1;
        while(k-->0){
            sum *= n--;
        }
        return sum;
    }
    //前面已经固定fixNum个数字，后面随便选
    int fullNumHead(int fixNum, int num){
        return fun_base_10_k(num)  - fun_A_n_k(10-fixNum, num);
    }
    //num 随便选，但不能有前缀0
    int fullNum(int num){
        if(num <= 1)return 0;
        return 9 * fullNumHead(1, num - 1);
    }
public:
    int numDupDigitsAtMostN(int N) {
        vector<int> bit;
        while(N>0) {
            bit.push_back(N%10);
            N /= 10;
        }

        int ans = 0;
        if(N == 1000000000){
            ans++;
            N--;
        }

        for(int i=1;i<bit.size();i++){
            ans += fullNum(i);
        }
        //printf("base ans=%d\n", ans);
        vector<int> have(10, 0);
        int diffNum = 0;
        int isSame = 0;
        for(int i = bit.size()-1;i>=0;i--){
            for(int j= (i==bit.size()-1)?1:0;j<bit[i];j++){
                if(have[j] || isSame){
                    ans += fun_base_10_k(i);
                }else{
                    ans += fullNumHead(diffNum+1, i);
                }
                //printf("i=%d j=%d have=%d ans=%d\n",i, j, have[j], ans);
            }
            if(!have[bit[i]]){
                diffNum++;
            }
            have[bit[i]]++;
            if(have[bit[i]] >1){
                isSame = 1;
            }
        }

        //n也是答案
        for(int i=0;i<10;i++){
            if(have[i]>1){
                ans++;
                break;
            }
        }
        return ans;
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

