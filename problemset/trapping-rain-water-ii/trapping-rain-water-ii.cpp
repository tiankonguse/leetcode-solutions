/*************************************************************************
  > File Name: trapping-rain-water-ii.cpp
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
    int xn; 
    int yn; 
    int flag[150][150];
    struct Point{
		Point(int x=0, int y=0, int z=0):x(x),y(y),z(z){}
		int x,y,z;//二维数组，左边代表x,右边代表y
		bool operator<(const Point &t2)const {
			return this->z > t2.z;
		}
	};
    priority_queue<Point> que;
    //由于当前的高度是周边最低的
    //所以内部凡是和这个点联通的，都可以计算出积水面积，病标记为不可用
    void dfs(int x, int y, int height, vector<vector<int> >& heightMap){
		static int dir[4][2] = {{0,-1},{0, 1},{1,0},{-1,0}};
        if(x < 0 || x >= xn || y < 0 || y >= yn){
            return;
        }
        
        //已经是废弃的坐标，不做任何处理
        if(flag[x][y] == -1) {
            return;
        }
        
        //这个节点比最小值高，不通
        if(heightMap[x][y] > height){
            //由于dfs访问到了，说明这个坐标可以当做边界了
            //还不在队列里面了，说明第一次变成边界
            if(flag[x][y] == 0){
                que.push( Point(x, y, heightMap[x][y]));
				//printf("<-- x=%d y=%d z=%d\n", x, y, heightMap[x][y]);
                flag[x][y] = 1;
            }
            return ;
        }
        
        //这个节点可以积水，进行计算
        ans += height - heightMap[x][y];
        //printf("x=%d y=%d z=%d height=%d inc=%d\n", x, y, heightMap[x][y], height, height - heightMap[x][y]);
		
        //已经积水，记为不可用
		flag[x][y] = -1;
        
        for(int i=0;i<4;i++){
            dfs(x+dir[i][0], y+dir[i][1], height, heightMap);
        }
    }
    
public:
    int trapRainWater(vector<vector<int> >& heightMap) {
        ans = 0;
		
        xn = heightMap.size();
		if(xn == 0){
			return 0;
		}
        yn = heightMap[0].size();
		if(yn == 0){
			return 0;
		}
        while(!que.empty()){
            que.pop();
        }
        
        for(int i=0; i< xn;i++){
            
            que.push( Point(i, 0, heightMap[i][0]));
            flag[i][0] = 1;
            
            que.push(Point(i, yn-1, heightMap[i][yn-1]));
            flag[i][yn-1] = 1;
        }
        for(int i=0;i<yn;i++){
            que.push(Point(0, i, heightMap[0][i]));
            flag[0][i] = 1;
            
            que.push(Point(xn-1, i, heightMap[xn-1][i]));
            flag[xn-1][i] = 1;
        }
        memset(flag, 0, sizeof(flag));
        
        //根据木桶原理，四边的最低点决定了水桶的积水大小
        while(!que.empty()){
            Point p = que.top();que.pop();
			//printf("--> x=%d y=%d z=%d\n", p.x, p.y, p.z);
            dfs(p.x, p.y, p.z, heightMap);
			//printf("\n");
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


void test(vector<vector<int> >& nums){
    Solution work;
    int ans;
    output("nums", nums);
    ans = work.trapRainWater(nums);
    output("ans", ans);
}

int main() {
    vector<vector<int> > nums;

    nums = {
      {1,4,3,1,3,2},
      {3,2,1,3,2,4},
      {2,3,3,2,3,1}
    };
    test(nums);

	
	nums = {{2,3,4},{5,6,7},{8,9,10},{11,12,13},{14,15,16}};
    test(nums);

    return 0;
}
