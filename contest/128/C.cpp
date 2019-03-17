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




const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();

typedef long long LL;
class Solution {
    bool check(int mid, vector<int>& weights, int D){
        int sum = 0;
        for(int i=0;i<weights.size();i++){
            if(sum < weights[i]){
                sum = mid;
                D--;
            }
            if(D < 0){
                return false;
            }
            sum -=  weights[i];
        }
        return true;
    }
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int maxAns = 0, minAns = weights[0];
        for(int i=0;i<weights.size();i++){
            maxAns += weights[i];
            minAns = max(minAns, weights[i]);
        }

        int midAns = 0;
        while(minAns < maxAns){
                midAns = (minAns + maxAns)/2;
            if(check(midAns, weights, D)){
               maxAns = midAns;
            }else{
                minAns = midAns + 1;
            }
        }
        return minAns;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.shipWithinDays(firstData, secondData);

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
    vector<int> first;
    int second;
    int expectAns;


    first = {1,2,3,4,5,6,7,8,9,10};
    second = 5;
    expectAns = 15;
    test(expectAns, first, second);


    first = {3,2,2,4,1,4};
    second = 3;
    expectAns = 6;
    test(expectAns, first, second);



    first = {1,2,3,1,1};
    second = 4;
    expectAns = 3;
    test(expectAns, first, second);

    return 0;
}

