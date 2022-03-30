/*************************************************************************
  > File Name: trapping-rain-water.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 13:50 2017/8/23
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
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
    int ans;
    int n;
    vector<int> flag;
    struct Point{
		Point(int x=0, int y=0):x(x),y(y){}
		int x,y;
		bool operator<(const Point &t2)const {
			return this->y > t2.y;
		}
	};
    priority_queue<Point> que;
    
    void dfs(int x, int y, vector<int>& height){
        static int dir[2] = {1, -1};
        if(x < 0 || x >= n){
            return ;
        }
        
        if(flag[x] == -1){
            return ;
        }
        
        if(height[x] > y){
            if(flag[x] == 0){
                que.push( Point(x, height[x]));
                flag[x] = 1;
            }
            return ;
        }
        
        ans += y - height[x];
        flag[x] = -1;
        for(int i=0;i<2;i++){
            dfs(x + dir[i], y, height);
        }
        
    }
    
public:
    int trap(vector<int>& height) {
        ans = 0;
        
        n = height.size();
        if(n <= 2){
            return 0;
        }
        
        while(!que.empty()){
            que.pop();
        }
        flag.clear();
        flag.resize (n, 0);
        
        que.push(Point(0, height[0]));
        flag[0] = 1;
        que.push(Point(n-1, height[n-1]));
        flag[n-1] = 1;
        
        while(!que.empty()){
            Point p = que.top();que.pop();
            dfs(p.x, p.y, height);
        }
		return ans;
    }
};

void output(char const* name, std::string &data){
    printf("%s:\n   %s\n", name, data.c_str());
    printf("\n");
}

void output(char const* name, int data){
    printf("%s:\n    %d\n", name, data);
    printf("\n");
}

void output(char const* name, vector<int>&data){
    printf("%s:", name);
    for(int i=0;i<data.size();i++){
        printf("%d ", data[i]);
    }
    printf("\n");
}

void output(char const* name, vector<vector<int>>&data){
    printf("%s:\n", name);
    for(int i=0;i<data.size();i++){
        output("    ", data[i]);
    }
    printf("\n");
}


void test(vector<int>& nums){
    Solution work;
    int ans;
    output("nums", nums);
    ans = work.trap(nums);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    test(nums);


    return 0;
}
