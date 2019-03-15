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
    int n;
    vector<int>  data;
    vector<int>  sum;
    int mod;

    void getsum() {
        sum[0] = data[0];
        for(int i=1; i<n; i++) {
            sum[i] = (sum[i-1] + data[i]) % mod;
        }
        printf("data: ");
        for(int i=0;i<n;i++){
            printf("%d ", data[i]);
        }
        printf("\n");
        printf("sum: ");
        for(int i=0;i<n;i++){
            printf("%d ", sum[i]);
        }
        printf("\n");
    }
public:
    int numPermsDISequence(string S) {
        n = S.size() + 1;
        data.resize(n, 1);
        sum.resize(n, 0);
        mod = 1000000007;

        getsum();

        for(int j=0; j<S.size(); j++) {
            if(S[j] == 'D') {
                for(int i=0; i<n; i++) {
                    data[i] = (sum[n-1] + mod - sum[i]) % mod;
                }
            } else {
                for(int i=n-1; i>0; i--) {
                    data[i] = sum[i-1];
                }
                data[0] = 0;
            }
            getsum();
        }
        return sum[n-1];
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

