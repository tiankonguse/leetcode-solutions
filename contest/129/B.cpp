/*************************************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 24 09:24:48 2019
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
    vector<vector<vector<int>>> numMap;
    vector<int> numBit;
public:
    Solution() {
        numMap.resize(10);
        for(int i=0; i<numMap.size(); i++) {
            numMap[i].resize(10);
        }

        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                int ij = i*j% 10;
                numMap[i][ij].push_back(j);
            }
        }
    }


    void fixSum(vector<int>& tmpSum, int pos) {
        while(tmpSum[pos] >= 10) {
            if(pos + 1 == tmpSum.size()) {
                tmpSum.push_back(0);
            }
            tmpSum[pos+1] += tmpSum[pos]/10;
            tmpSum[pos] = tmpSum[pos] % 10;
            pos++;
        }
    }

    bool check(vector<int>& sum){
        for(int i=0;i<sum.size();i++){
            if(sum[i] != 1){
                return false;
            }
        }
        return true;
    }

    int dfs(int pos, vector<int>& sum, vector<int> vecAns) {
        printf("pos=%d\n", pos);
        //output("sum", sum);
        //output("vecAns", vecAns);
        int expNum = (11 - sum[pos]) % 10;
        vector<int>& numSet = numMap[numBit[0]][expNum];
        if(numSet.size() == 0) {
            return -1;
        }
        int ans = -1;
        for(int i=0; i<numSet.size(); i++) {
            int val = numSet[i];
            vecAns.push_back(val);

            vector<int> tmpSum = sum;
            for(int j=0; j<numBit.size(); j++) {
                int nowPos = j + pos;
                tmpSum[nowPos] += val * numBit[j];
                fixSum(tmpSum, nowPos);
            }

            int tmpAns = -1;
            if(check(tmpSum)) {
                //output("numBit ans", numBit);
                //output("vecAns ans", vecAns);
                //output("tmpSum ans", tmpSum);

                tmpAns =  tmpSum.size();
            }else{
                tmpAns = dfs(pos+1, tmpSum, vecAns);
            }
            if(ans == -1) {
                ans = tmpAns;
            } else if(tmpAns == -1){
            }else{
                ans = min(ans, tmpAns);
            }
            vecAns.pop_back();
        }
        return ans;
    }

    int smallestRepunitDivByK(int K) {
        while(K>0) {
            numBit.push_back(K%10);
            K/=10;
        }
        vector<int> sum;
        sum.push_back(0);
        vector<int> vecAns;
        return dfs(0,  sum, vecAns);
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.smallestRepunitDivByK(firstData);

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
    expectAns = 1;
    test(expectAns, first);



    first = 2;
    expectAns = -1;
    test(expectAns, first);

    first = 3;
    expectAns = 3;
    test(expectAns, first);


    for(int i=113;i<=100000;i++){
        first = i;
        expectAns = 3;
        test(expectAns, first);
    }

    return 0;
}
