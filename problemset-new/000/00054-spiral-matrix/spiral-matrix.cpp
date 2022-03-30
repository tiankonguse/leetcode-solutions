/*************************************************************************
    > File Name: spiral-matrix.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 00:05:51 2019
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
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        if(matrix.size() == 0) {
            return ans;
        }

        //top , right, bottom, left
        enum {TOP = 0, RIGHT = 1, BOTTOM = 2, LEFT = 3};
        int base[4] = {0, matrix[0].size()-1, matrix.size() - 1, 0};
        int baseInc[4] = {1, -1, -1, 1};
        int xyInc[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        int step = 0, x = 0, y = 0;
        while(base[TOP] <= base[BOTTOM] && base[LEFT] <= base[RIGHT]) {
            while(x >= base[TOP] && x <= base[BOTTOM] && y >= base[LEFT] && y <= base[RIGHT]) {
                ans.push_back(matrix[x][y]);
                x += xyInc[step][0];
                y += xyInc[step][1];
            }
            //越界了，倒退回去
            x -= xyInc[step][0];
            y -= xyInc[step][1];
            base[step] += baseInc[step];

            step = (step+1)%4;
            x += xyInc[step][0];
            y += xyInc[step][1];
        }
        return ans;
    }
};
template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& data, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.spiralOrder(data);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("data", data);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<vector<int>> data;
    vector<int> expectAns;

    data = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    expectAns = {1,2,3,6,9,8,7,4,5};
    test(expectAns, data);

    data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
    };
    expectAns = {1,2,3,4,8,12,11,10,9,5,6,7};
    test(expectAns, data);


    data = {
        { 1 }
    };
    expectAns = {1};
    test(expectAns, data);


    data = {
        { 1},
        { 4},
        { 7}
    };
    expectAns = {1,4,7};
    test(expectAns, data);

    return 0;
}
