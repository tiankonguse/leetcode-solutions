/*************************************************************************
> File Name: container-with-most-water.cpp
> Author: tiankonguse(skyyuan)
> Mail: i@tiankonguse.com 
> Created Time: 2015年05月20日 13:03:35
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

class Solution {
    typedef int Type;
    int Calc(Type a, Type pos, vector<int>&height) {
        return (height[sta[a]] + height[pos]) * (pos - sta[a]) / 2;
    }
    vector<int>sta;
    int ans;

    // left,right sta 
    // pos height
    int Solve(int left, int right, int pos, vector<int>&height) {
        int mid_left, mid_right;
        int mid_left_value, mid_right_value;
        int Golden_Section ,len, tmp;
        bool left_scale = true;

        mid_left = right - Golden_Section;
        mid_left_value = Calc(mid_left, pos, height);
        printf("left=%d right=%d\n", left, right);
        printf("p=%d size=%d\n",pos, (int)sta.size());
        while (left < right) {
            printf("l=%d r=%d\n",left,right);
            if(left + 5 >= right ){
                mid_right_value = Calc(right, pos, height);
                mid_left_value = Calc(left, pos, height);
                if(mid_left_value >= mid_right_value){
                    right = right - 1;
                }else{
                    left = left + 1;
                }
                continue;
            }
            Golden_Section = (right - left) / 3;

            mid_right = right - Golden_Section;
            mid_right_value = Calc(mid_right, pos, height);

            mid_left = left + Golden_Section;
            mid_left_value = Calc(mid_left, pos, height);

            if (mid_left_value <= mid_right_value) {
                left = mid_left;
            } else {
                right = mid_right;
            }
        }

        mid_left_value = Calc(left, pos, height);
        printf("left=%d pos=%d val=%d\n", left, pos, mid_left_value);
        return mid_left_value;
    }
void updateAns(int pos, int& ans, vector<int>&height){
    int tmpAns = 0;
    tmpAns = Solve(0, sta.size()-1, pos, height);

    if(tmpAns > ans){
        ans = tmpAns;
    }
}

    void updateSta(int pos, vector<int>&height){
        printf("lastPos=%d lastVal=%d pos=%d posVal=%d\n", sta.back(), height[sta.back()], pos, height[pos]);
        if(height[sta.back()] < height[pos]){
            sta.push_back(pos);
        }
    }

public:
    int maxArea(vector<int>& height) {
        sta.clear();
        int ans = 0;
        int size = height.size();
        int pos = 0;

        if(size <= 1){
            return ans;
        }

        sta.push_back(pos);
        pos = pos + 1;

        for(;pos < size;pos++){
            updateAns(pos, ans, height);
            updateSta(pos, height);
        }
        return ans;
    }
    };

void output(char  const* name, vector<int>&height, int ans){
    printf("height:");
    for(int i=0;i<height.size();i++){
        printf(" %d", height[i]);
    }
    printf("\n");
    printf("ans=%d\n",ans);
}

void test(vector<int>&height){
    Solution work;
    int ans;
    ans = work.maxArea(height);
    output("height", height, ans);
}

int main() {
    vector<int>height;

    //    height = {};
    //    test(height);
    //
    //    height = {2};
    //    test(height);
    //
    //    height = {1,3,4};
    //    test(height);
    //
    //    height = {5,7,1,4};
    //    test(height);
    //
    //    height = {9,2,4,4};
    //    test(height);
    //
    //    height = {1,0,3,1};
    //    test(height);
    //
    //    height = {3,2,1,3};
    //    test(height);

    height = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
    test(height);

    return 0;
}
