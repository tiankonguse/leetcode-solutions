/*************************************************************************
  > File Name: house-robber.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月16日 13:20:49
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
    int max(int a, int b){
        if(a>b){
            return a;
        }else{
            return b;
        }
    }
public:
    int rob(vector<int> &vec) {

        int size = vec.size();

        if(size == 0){
            return 0;
        }

        vector<int>robbing(size, 0);//rob this house
        vector<int>left(size, 0);//not rob this house

        robbing[0] = vec[0];
        left[0] = 0;

        for(int i=1;i<size;i++){
            left[i] = max(left[i-1], robbing[i-1]);
            robbing[i] = vec[i] + left[i-1];
        }
        return max(left[size-1], robbing[size-1]);
    }
};

void output(vector<int>&vec){
    int size = vec.size();
    printf("size=%d\n", size);
    for(int i=0;i<size;i++){
        printf("%d ", vec[i]);
    }
    printf("\n");
}

void test(){
    Solution work;

    vector<int>vec;
    int ans = 0;

    ans = work.rob(vec);
    output(vec);
    printf("ans = %d\n", ans);
    
    vec.push_back(34);
    ans = work.rob(vec);
    output(vec);
    printf("ans = %d\n", ans);
    
    vec.push_back(3);
    ans = work.rob(vec);
    output(vec);
    printf("ans = %d\n", ans);
    
    vec.push_back(2);
    ans = work.rob(vec);
    output(vec);
    printf("ans = %d\n", ans);
    
    vec.push_back(5353);
    ans = work.rob(vec);
    output(vec);
    printf("ans = %d\n", ans);
}

int main() {
    test();
    return 0;
}
