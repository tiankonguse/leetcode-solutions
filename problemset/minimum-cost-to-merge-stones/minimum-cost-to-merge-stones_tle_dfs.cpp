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



class Solution {
    int ans;

    void dfs(vector<int> stones, int K, int nowAns) {
        if(nowAns >= ans) { //剪枝，已经比临时最优值差了
            return;
        }

        if(stones.size() == 1) { //dfs 出口
            if(nowAns < ans) {
                ans  = nowAns;
            }
            return ;
        }


        int left=0;
        int sum =0;
        for(int i=0; i<stones.size(); i++) {
            //[i, i+K-1]之间的合并
            sum += stones[i];
            if(i < K-1) {
                //sum 不足k个
                continue;
            } else if(i == K - 1) {
                //sum 首次到达k个
            } else {
                //sum 多一个
                sum -= stones[i-K];
            }
            //够k个了

            vector<int> tmpstones = stones;
            left = i-K+1;
            tmpstones[left] = sum;
            tmpstones.erase(tmpstones.begin() + left + 1, tmpstones.begin() + left + K);
            dfs(tmpstones, K, nowAns + sum);
        }
    }

    int greedyStones(vector<int> stones, int K) {
        int tmpAns =0;
        while(stones.size() > 1) {
            int left=0;
            int sum =0;
            int minsum = 0;
            int minleft = 0;
            for(int i=0; i<stones.size(); i++) {
                sum += stones[i];

                if(i < K) {
                    //first sum
                    left = 0;
                    minsum = sum;
                    continue;
                }

                sum -= stones[i-K];
                if(sum < minsum) {
                    minsum = sum;
                    minleft = i-K+1;
                }
            }
            tmpAns += minsum;
            stones[minleft] = minsum;
            stones.erase(stones.begin() + minleft + 1, stones.begin() + minleft + K);
        }
        return tmpAns;
    }
public:
    int mergeStones(vector<int> stones, int K) {
        //if has ans
        if((stones.size() - 1) % (K - 1) != 0) {
            return -1;
        }

        ans = greedyStones(stones, K);
        dfs(stones, K, 0);
        return ans;
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
    if(!check) {
        printf("index %d: NO\n", index);
        output("stones", stones);
        output("K", K);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }

}

int main() {
    vector<int> data;
    int K;
    int expectAns;

    data = {3,2,4,1};
    K = 2;
    expectAns = 20;
    test(data, K, expectAns);

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



    data = {69,39,79,78,16,6,36,97,79,27,14,31,4};
    K = 2;
    expectAns = 40;
    test(data, K, expectAns);
    return 0;
}

