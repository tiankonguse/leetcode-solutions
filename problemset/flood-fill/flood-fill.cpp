/*************************************************************************
    > File Name: flood-fill.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr  9 00:26:26 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image.size() == 0 || image[0].size() == 0)
            return image;
        int oldColor = image[sr][sc];
        if(newColor == oldColor)
            return image;

        int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        stack<pair<int, int>> sta;
        int n = image.size();
        int m = image[0].size();

        image[sr][sc] = newColor;
        sta.push(make_pair(sr, sc));

        while(!sta.empty()) {
            auto p = sta.top();
            sta.pop();
            for(int i=0; i<4; i++) {
                sr = p.first + dir[i][0];
                sc = p.second + dir[i][1];
                if(sr < 0 || sr >= n || sc < 0 || sc >= m)
                    continue;
                if(image[sr][sc] != oldColor)
                    continue;
                image[sr][sc] = newColor;
                sta.push(make_pair(sr, sc));
            }
        }
        return image;
    }
};

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<vector<int>> first;
    int second;
    int third;
    int fouth;
    vector<vector<int>> expectAns;

    first = {{1,1,1},{1,1,0},{1,0,1}};
    second = 1;
    third = 1;
    fouth = 2;
    expectAns = {{2,2,2},{2,2,0},{2,0,1}};
    TEST_SMP4(Solution, floodFill, expectAns, first,second,third, fouth);


    return 0;
}
