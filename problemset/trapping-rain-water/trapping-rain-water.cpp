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

struct Node{
	Node(int pos = 0, int val = 0):pos(pos), val(val){}
	int pos;
	int val;
};

class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
		stack<Node> sta;
		sta.push(Node(-1, 0));
		
		Node left, right;
		int bottom;
		for(int i=0;i<height.size();i++){
			left = sta.top();
			right.pos = i;
			right.val = height[i];
			
			//递减的，需要入栈
			if(left.val > right.val){
				sta.push(right);
				continue;
			}
			
			//相等需要修改位置为最右边的位置
			if(left.val == right.val){
				sta.pop();
				sta.push(right);
				continue;
			}
			
			//大于的可能可以存水
			bottom = left.val;
			sta.pop();
			
			while(!sta.empty()){
				left = sta.top();
				
				//有个凹槽，但是右边比较低
				if(left.val > right.val){
					//printf("i = %2d  bottom = %2d val = %2d left = %2d right = %2d inc=%2d\n", i, bottom, right.val, left.pos, right.pos, (right.val - bottom) * (right.pos - left.pos - 1));
					ans += (right.val - bottom) * (right.pos - left.pos - 1);
					break;
				}
				
				//有个凹槽，但是左边低，还需要出栈
				ans += (left.val - bottom) * (right.pos - left.pos - 1);
				//printf("i = %2d  bottom = %2d val = %2d left = %2d right = %2d inc = %2d\n", i, bottom, left.val, left.pos, right.pos, (left.val - bottom) * (right.pos - left.pos - 1));
				
				bottom = left.val;
				sta.pop();
			}
			
			sta.push(right);
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
