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
    map<int,int>m;//<val, times>
    vector<int>targetList;
    int ans;
    int expAns;
    int target;
    int targetSize;

    int abs(int a){
        if(a < 0){
            return -a;
        }else{
            return a;
        }
    }

    void updateAns(int a, int b){
        int sum = a + b;
        int left = 0;
        int right = targetSize - 1;
        int mid;

        while(left + 3 < right){
            mid = (left + right)/2;
            if(targetList[mid] > sum){
                right = mid;
            }else{
                left = mid ;
            }
        }

        int c;
        int tmpExpAns;
        for(left -=3, right +=3;left <= right;left++){
            if(left <0 || left >= targetSize){
                continue;            
            }
            c = target - targetList[left];
            sum = a + b + c;
            tmpExpAns = abs(sum - target);
            if(tmpExpAns < expAns){
                if(a == c && b == c && m[c] < 3){
                    continue;
                }
                if((b == c || a == c) && m[c] < 2){
                    continue;
                }
                expAns = tmpExpAns;
                ans = sum;
            }
        }

    }

    public:
    int threeSumClosest(vector<int> &nums, int target) {
        m.clear();
        targetList.clear();
        
        this->target = target;

        ans = nums[0] + nums[1] + nums[2];
        expAns = abs(ans - target);

        for(int i=0;i<nums.size();i++){
            if(m.find(nums[i]) == m.end()){
                m[nums[i]] = 1;
                targetList.push_back(target - nums[i]);
            }else{
                m[nums[i]] = m[nums[i]] + 1;
            }
        }

        sort(targetList.begin(), targetList.end()); 
        targetSize = targetList.size();


        for(map<int,int>::iterator i=m.begin(); i != m.end();i++){
            for(map<int,int>::iterator j = i; j != m.end(); j++){
                if(i == j && i->second == 1){
                    continue;
                }
                updateAns(i->first, j->first);
            }
        }

        return ans;
    }
};

int main() {

    Solution solution;
    vector<int> array;
    
    array = {-1, -4, 2, 1};
    printf("%d\n", solution.threeSumClosest(array, 1));
    return 0;
}
