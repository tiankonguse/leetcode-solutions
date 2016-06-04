/*************************************************************************
  > File Name: 3sum-closest.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年03月31日 14:23:03
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
    int threeSumClosest(vector<int> &array, int target) {
        int ans = array[0] + array[1] + array[2];
        int minSum = abs(ans - target);

        int sum;

        int size = array.size();
        for(int i=0;i<size;i++){
            for(int j=i+1;j<size;j++){
                for(int k=j+1;k<size;k++){
                    sum = array[i] + array[j] + array[k];
                    if(abs(sum - target) < minSum){
                        minSum = abs(sum - target);
                        ans = sum;
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
        
    Solution solution;
    vector<int> array;
    array.push_back(-1);
    array.push_back(-4);
    array.push_back(2);
    array.push_back(1);
    printf("%d\n", solution.threeSumClosest(array, 1));
    return 0;
}
