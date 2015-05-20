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
    double const scale = (sqrt(5.0) - 1) / 2;
    int Calc(Type a, Type pos) {
        return (height[sta[a]] + height[pos]) * (pos - sta[a]) / 2;
    }
    vector<int>sta;
    vector<int>height;
    int ans;


    int Solve(int left, int right, int pos) {
        int mid_left, mid_right;
        int mid_left_value, mid_right_value;
        int Golden_Section ,len, tmp;
        bool left_scale = true;

        len = right - left + 1;
        Golden_Section = scale * len;
        mid_left = right - Golden_Section;
        mid_left_value = Calc(mid_left, pos);
        
        while (left < right) {
            printf("l=%d r=%d\n", left, right);
            if(left_scale) {
                mid_right = left + Golden_Section;
                mid_right_value = Calc(mid_right, pos);
            } else {
                mid_left = right - Golden_Section;
                mid_left_value = Calc(mid_left, pos);
            }
            tmp = len;
            len = Golden_Section;
            Golden_Section = tmp - Golden_Section;
            if (mid_left_value <= mid_right_value) {
                left = mid_left;
                left_scale = true;
                mid_left = mid_right;
                mid_left_value = mid_right_value;
            } else {
                right = mid_right;
                left_scale = false;
                mid_right = mid_left;
                mid_right_value = mid_left_value;
            }
        }
        return mid_left_value;
    }
    void updateAns(int pos, int& ans){
        int tmpAns = 0;
        tmpAns = Solve(0, sta.size(), pos);

        if(tmpAns > ans){
            ans = tmpAns;
        }
    }

    void updateSta(int pos){
        if(sta.back() < height[pos]){
            sta.push_back(pos);
        }
    }

public:
    int maxArea(vector<int>& height) {
        sta.clear();
        this->height = height;
        int ans = 0;
        int size = height.size();
        int pos = 0;

        if(size <= 1){
            return ans;
        }

        sta.push_back(pos);
        pos = pos + 1;

        for(;pos < size;pos++){
            updateAns(pos, ans);
            updateSta(pos);
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

    height = {};
    test(height);

    height = {2};
    test(height);

    height = {1,3,4};
    test(height);

    height = {5,7,1,4};
    test(height);

    height = {9,2,4,4};
    test(height);

    height = {1,0,3,1};
    test(height);
    
    height = {3,2,1,3};
    test(height);

    return 0;
}
