/*************************************************************************
    > File Name: max-consecutive-ones-iii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri Mar  8 23:34:41 2019
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
public:
    int longestOnes(vector<int>& data, int k) {
        int zeroNum = 0;
        queue<int> que;
        int ans = 0;

        for(int i = 0; i<data.size(); i++) {
            que.push(data[i]);
            if(data[i] == 0) {
                zeroNum++;
            }
            if(zeroNum > k) {
                //zero too more
                while(!que.empty() && zeroNum > k) {
                    if(que.front() == 0) {
                        zeroNum--;
                    }
                    que.pop();
                }
            }
            if(ans < que.size()) {
                ans = que.size();
            }
        }

        return ans;
    }
};

template <class ansType, class dataType1, class dataType2>
void test(dataType1& A, dataType2 K, ansType& expectAns) {
    Solution work;
    ansType ans;
    ans = work.longestOnes(A, K);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("A", A);
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

    data = {1,1,1,0,0,0,1,1,1,1,0};
    K = 2;
    expectAns = 6;
    test(data, K, expectAns);

    data = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    K = 3;
    expectAns = 10;
    test(data, K, expectAns);

    return 0;
}
