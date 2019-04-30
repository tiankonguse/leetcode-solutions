/*************************************************************************
    > File Name: escape-a-large-maze.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 29 00:06:47 2019
    > link:
    > No: 1036. Escape a Large Maze
    > Contest: https://leetcode.com/contest/weekly-contest-134/problems/escape-a-large-maze/
 ************************************************************************/

#include "../../include/base.h"

int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
class Solution {
    set<pair<int, int>> setBlocked;
    int maxX = 1000000;
    int maxY = 1000000;
    //0 <= x, y < 10^6
    bool isBlock(int x, int y) {
        if(setBlocked.find({x,y}) != setBlocked.end()) {
            return true;
        }
        return false;
    }
    bool isFindBlock(vector<int>& source, vector<int>& target) {
        int maxStep = 101 * 201;
        set<pair<int, int>> setAfter;
        queue<pair<int, int>> que;

        setAfter.insert({source[0], source[1]});
        que.push({source[0], source[1]});

        int x0, y0;
        while(maxStep > 0 && !que.empty()) {
            auto p = que.front();
            que.pop();
            maxStep--;
            for(int i=0; i<4; i++) {
                x0 = p.first + dir[i][0];
                y0 = p.second + dir[i][1];
                if(x0 < 0 || x0 >= maxX || y0 < 0 || y0 >= maxY) {
                    continue;
                }
                if(x0 == target[0] && y0 == target[1]) {
                    return false;
                }
                if(isBlock(x0, y0)) {
                    continue;
                }
                if(setAfter.find({x0, y0}) != setAfter.end()) {
                    continue;
                }
                setAfter.insert({x0, y0});
                que.push({x0, y0});
            }
        }
        return maxStep != 0;
    }

public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        for(int i=0; i<blocked.size(); i++) {
            setBlocked.insert({blocked[i][0], blocked[i][1]});
        }
        if(isBlock(source[0], source[1]) || isBlock(target[0], target[1])) {
            return false;
        }
        if(isFindBlock(source, target) || isFindBlock(target, source)) {
            return false;
        }
        return true;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
#define CLASS Solution
#define FUNCTION isEscapePossible

    vector<vector<int>> first;
    vector<int> second;
    vector<int> third;
    bool expectAns;

    first = {{0,1},{1,0}};
    second =  {0,0};
    third = {0,2};
    expectAns = false;
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);


    first =  {};
    second = {0,0};
    third = {999999,999999};
    expectAns = true;
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);


    first =  {{100059,100063},{100060,100064},{100061,100065},{100062,100066},{100063,100067},{100064,100068},{100065,100069},{100066,100070},{100067,100071},{100068,100072},{100069,100073},{100070,100074},{100071,100075},{100072,100076},{100073,100077},{100074,100078},{100075,100079},{100076,100080},{100077,100081},{100078,100082},{100079,100083},{100080,100082},{100081,100081},{100082,100080},{100083,100079},{100084,100078},{100085,100077},{100086,100076},{100087,100075},{100088,100074},{100089,100073},{100090,100072},{100091,100071},{100092,100070},{100093,100069},{100094,100068},{100095,100067},{100096,100066},{100097,100065},{100098,100064},{100099,100063},{100098,100062},{100097,100061},{100096,100060},{100095,100059},{100094,100058},{100093,100057},{100092,100056},{100091,100055},{100090,100054},{100089,100053},{100088,100052},{100087,100051},{100086,100050},{100085,100049},{100084,100048},{100083,100047},{100082,100046},{100081,100045},{100080,100044},{100079,100043},{100078,100044},{100077,100045},{100076,100046},{100075,100047},{100074,100048},{100073,100049},{100072,100050},{100071,100051},{100070,100052},{100069,100053},{100068,100054},{100067,100055},{100066,100056},{100065,100057},{100064,100058},{100063,100059},{100062,100060},{100061,100061},{100060,100062}};
    second = {100079,100063};
    third = {999948,999967};
    expectAns = false;
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);
    return 0;
}
