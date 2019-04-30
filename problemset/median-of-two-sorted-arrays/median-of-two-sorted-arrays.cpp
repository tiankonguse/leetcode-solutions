/*************************************************************************
  > File Name: median-of-two-sorted-arrays.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年05月19日 20:49:56
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
    int find(vector<int>&first, vector<int>&second, int ansPoint){
        int firstPoint = 0;
        int secondPoint = 0;
        int firstSize = first.size();
        int secondSize = second.size();

        int ans = 0;
        while(ansPoint >= 0){
            if(firstPoint < firstSize && secondPoint < secondSize){
                if(first[firstPoint] <= second[secondPoint]){
                    ans = first[firstPoint];
                    firstPoint = firstPoint + 1;
                }else{
                    ans = second[secondPoint];
                    secondPoint = secondPoint + 1;
                  }
            }else if(firstPoint < firstSize && secondPoint == secondSize){
                ans = first[firstPoint];
                firstPoint = firstPoint + 1;
            }else if(firstPoint == firstSize && secondPoint < secondSize){
                ans = second[secondPoint];
                secondPoint = secondPoint + 1;
            }else{
                         
            }
            ansPoint = ansPoint - 1;
            //printf("ans=%d ansPoint=%d\n", ans, ansPoint);
        }
        //printf("ans=%d\n",ans);
        return ans;
    
    }
    double findOdd(vector<int>&first, vector<int>&second){
        int firstSize = first.size();
        int secondSize = second.size();
        int ansPoint = (firstSize + secondSize) / 2;
        double ans = 0;
        ans = ans + find(first, second, ansPoint);
        return ans;
    }

    double findEven(vector<int>&first, vector<int>&second){
        int firstSize = first.size();
        int secondSize = second.size();
        int ansPoint = (firstSize + secondSize) / 2;
        double ans = 0;
        ans = ans + find(first, second, ansPoint);
        
        ansPoint = ansPoint - 1;
        ans = ans + find(first, second, ansPoint);
        return ans/2;
    }
public:
    double findMedianSortedArrays(vector<int>& first, vector<int>& second) {
        int allNum = first.size() + second.size();
        if(allNum % 2 == 0){
            return findEven(first, second);
        }else{
            return findOdd(first, second);
        }
    }
};

void output(char const* name, vector<int>&list){
    printf("%s(%d) = ", name, list.size());
    for(int i=0;i<list.size();i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}

void test(vector<int>&first, vector<int>&second){
    Solution work;
    double ans;
    output("first", first);
    output("second", second);
    ans = work.findMedianSortedArrays(first, second);
    printf("ans=%lf\n",ans);
}

int main() {
    vector<int>first;
    vector<int>second;

    first = {1,2,3,4};
    second = {1,2,3,4};
    test(first, second);
    

    first = {};
    second = {};
    test(first, second);
    
    first = {1};
    second = {};
    test(first, second);
    
    first = {1,2};
    second = {};
    test(first, second);
    
    first = {1,2};
    second = {3};
    test(first, second);
    return 0;
}
