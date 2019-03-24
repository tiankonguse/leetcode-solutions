/*************************************************************************
    > File Name: D.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 24 09:25:00 2019
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
    bool queryString(string S, int N) {
        set<int> have;
        for(int i=0;i<S.size();i++){
            long long sum = 0;
            for(int j=i;j<S.size();j++){
                sum = sum *2 + S[j] - '0';
                if(sum > N){
                    break;
                }
                if(sum == 0){
                    continue;
                }
                have.insert((int)sum);
            }
        }
        if(have.size() == N){
            return true;
        }

        return false;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.queryString(firstData, secondData);

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
    int second;
    int expectAns;


    first = "0110";
    second = 3;
    expectAns = 1;
    test(expectAns, first, second);




    first = "0110";
    second = 4;
    expectAns = 0;
    test(expectAns, first, second);

    return 0;
}
