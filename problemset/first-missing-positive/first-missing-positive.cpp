/*************************************************************************
  > File Name: first-missing-positive.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年03月31日 13:40:46
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
    int firstMissingPositive(int A[], int n) {
        int bit = 32;
        unsigned int one = 1;
        int size = n/bit + bit;
        unsigned int array[size];
        
        for(int i=0;i<size;i++){
            array[i] = 0;
        }


        int ans = 1;
        for(int i=0;i<n;i++){
            if(A[i] > 0){
                array[A[i]/bit] |= one<<(A[i]%bit);
                while( (array[ans/bit]>>(ans%bit))&1){
                    ans++;
                }
            }
        }
        return ans;
    }
};

int main() {
    


    return 0;
}
