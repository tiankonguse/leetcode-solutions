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
    void updateAns(vector<int>&sta, vector<int>&height, int pos, int& ans){
        int tmpAns = 0;
        int tmpHeight;
        for(int i=0;i<sta.size();i++){
            tmpHeight = height[sta[i]];
            tmpAns = (pos - sta[i]) * (tmpHeight + height[pos]) / 2;
            if(tmpAns > ans){
                ans = tmpAns;
            }
        }
    }

    void updateSta(vector<int>&sta, vector<int>&height, int pos){
        if(sta.back() < height[pos]){
            sta.push_back(pos);
        }
    }

public:
    int maxArea(vector<int>& height) {
        vector<int>sta;
        int ans = 0;
        int size = height.size();
        int pos = 0;

        if(size <= 1){
            return ans;
        }
        
        sta.push_back(pos);
        pos = pos + 1;

        for(;pos < size;pos++){
            updateAns(sta, height, pos, ans);
            updateSta(sta, height, pos);
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
