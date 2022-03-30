/*************************************************************************
    > File Name: rectangle-area-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年02月28日 20:15:53
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

typedef long long LL;

bool compare(const vector<int> &first,const vector<int> &second) {
    for(int i=0; i<4; i++) {
        if(first[i] != second[i]) {
            return first[i] < second[i];
        }
    }
    return first[0] < second[0];
}

class Solution {
    map<int, int> mapToIndex;
    vector<int> vecToValue;
    vector<int>dis; //面积计算到哪里了，高度, -1代表未计算

    long long ans;
    void addIndex(int x) {
        if(mapToIndex.find(x) == mapToIndex.end()) {
            mapToIndex[x] = vecToValue.size();
            vecToValue.push_back(x);
        }
    }
    void addRectangle(vector<int>& rectangle) {
        int y1Index = mapToIndex[rectangle[1]];
        int y2Index = mapToIndex[rectangle[3]];
        // y1Pos < y2Pos
        int x1Indxex = mapToIndex[rectangle[0]];
        int x2Indxex = mapToIndex[rectangle[2]];
        // x1Indxex < x2Indxex
        //printf("(%d,%d), (%d,%d)\n", x1Indxex,y1Index,x2Indxex,y2Index);

        for(int i=y1Index; i< y2Index; i++) {
            if(x1Indxex >= dis[i]) {
                //新的小矩形
                //printf("1 %d: %lld,%lld %d,%d\n", i,vecToValue[i+1], vecToValue[i],x2Indxex, x1Indxex );
                ans += (long long)(vecToValue[i+1] - vecToValue[i]) * (long long)(vecToValue[x2Indxex] - vecToValue[x1Indxex]);
                dis[i] = x2Indxex;
            } else if(x2Indxex <= dis[i]) {
                //完全覆盖，啥都不做
                //printf("2 %d:none\n",i);
            } else {
                //遮住一半
                //printf("3 %d: %lld,%lld %d,%d\n", i,vecToValue[i+1], vecToValue[i],x2Indxex,dis[i]);
                ans += (long long)(vecToValue[i+1] - vecToValue[i]) * (long long)(vecToValue[x2Indxex] - vecToValue[dis[i]]);
                dis[i] = x2Indxex;
            }
        }
    }
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        const long long mod = 1000000000 + 7;
        //离线化
        mapToIndex.clear();
        vecToValue.clear();
        dis.clear();

        for(int i=0; i<rectangles.size(); i++) {
            for(int j=0; j<rectangles[i].size(); j++) {
                addIndex(rectangles[i][j]);
            }
        }

        //重新编号
        sort(vecToValue.begin(),vecToValue.end());

        for(int i=0; i<vecToValue.size(); i++) {
            mapToIndex[vecToValue[i]] = i;
            dis.push_back(-1);
            //printf("%d: %lld\n", i,vecToValue[i] );
        }


        //对所有矩阵排序
        sort(rectangles.begin(), rectangles.end(), compare);

        for(int i=0; i<rectangles.size(); i++) {
           // printf("data: (%d,%d), (%d,%d)\n", mapToIndex[rectangles[i][0]], mapToIndex[rectangles[i][1]], mapToIndex[rectangles[i][2]], mapToIndex[rectangles[i][3]]);
            //printf("data: (%lld,%lld), (%lld,%lld)\n", rectangles[i][0],rectangles[i][1],rectangles[i][2],rectangles[i][3]);

        }
        ans  = 0;
        for(int i=0; i<rectangles.size(); i++) {
            addRectangle(rectangles[i]);
        }

        return ans % mod;
    }
};

void test(vector<vector<int>>& rectangles, LL expectAns) {
    Solution work;
    int ans;
    ans = work.rectangleArea(rectangles);
    output("rectangles", rectangles);
    output("ans", ans);
    output("expectAns", expectAns);

}

int main() {
    vector<vector<int>> rectangles;
    LL expectAns;


    rectangles = {{0,0,2,2},{1,0,2,3},{1,0,3,1}};
    expectAns = 6;
    test(rectangles, expectAns);


    rectangles = {{0,0,1000000000,1000000000}};
    expectAns = 49;
    test(rectangles, expectAns);

    return 0;
}
