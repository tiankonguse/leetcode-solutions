/*************************************************************************
    > File Name: C.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月15日 16:42:56
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
    vector<int> sum;
    vector<int> bit;
    int n;

    int calAns(int pos, int val) {
        //找到比当前位小的个数
        int ans = sum[val];
        while(pos > 0) {
            ans *= n;
            pos--;
        }
        return ans;
    }
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        n = D.size();
        have.resize(10,0);
        for(int i=0; i<D.size(); i++) {
            have[D[i][0]-'0'] = 1;
        }

        sum.resize(10,0);
        for(int i=1; i<10; i++) {
            sum[i] = sum[i-1] + have[i-1];
        }

        while(N>0) {
            bit.push_back(N%10);
            N /= 10;
        }

        int pos = bit.size() - 1;
        int ans = 0;

        if( bit.size() > 1) {
            ans = 0;
            int tmpSUm = 1;
            for(int i=1;i<bit.size();i++){
                tmpSUm = tmpSUm * n;
                ans += tmpSUm;
            }
        }

        for(pos= bit.size() -1; pos>=0; pos--) {
            ans += calAns(pos, bit[pos]);
            if(have[bit[pos]] == 0) {
                break;
            }
        }
        if(pos == -1) {
            ans++;
        }
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.atMostNGivenDigitSet(firstData, secondData);

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
    vector<string> first;
    int second;
    int expectAns;


    first = {"1","3","5","7"};
    second = 100;
    expectAns = 20;
    test(expectAns, first, second);



    first = {"1"};
    second = 11;
    expectAns = 2;
    test(expectAns, first, second);

    first = {"1","4","9"};
    second = 1000000000;
    expectAns = 29523;
    test(expectAns, first, second);


    return 0;
}

