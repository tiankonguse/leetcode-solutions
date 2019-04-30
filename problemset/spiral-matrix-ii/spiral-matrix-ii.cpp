/*************************************************************************
  > File Name: spiral-matrix-ii.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年03月31日 13:53:14
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
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int> > ans;
        
        ans.resize(n);
        for(int i=0;i<n;i++){
            ans[i].resize(n, 0);
        }
        int sum = n * n;

        int top = 0;
        int bottom = n-1;
        int left = 0;
        int right = n-1;

        for(int k=1,i=-1,j=-1;k<=sum;){
            for(i++,j++;j<=right && k <= sum;j++){
                ans[i][j] = k++;
            }
            top++;

            for(i++,j--;i<=bottom && k<=sum;i++){
                ans[i][j] = k++;
            }
            right--;

            for(i--,j--;j>=left && k <= sum;j--){
                ans[i][j] = k++;
            }
            bottom--;

            for(i--,j++;i>=top && k<=sum;i--){
                ans[i][j] = k++;
            }
            left++;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    int n = 4;
    vector<vector<int> > ans = solution.generateMatrix(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
