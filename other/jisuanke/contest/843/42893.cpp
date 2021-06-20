/*************************************************************************
  > File Name: 42893.cpp
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


int main() {
    int t;
    int n;
    LL val;
    
    scanf("%d", &t);
    while(t--){
        scanf("%d",&n);
        
        map<LL, int> m;
        priority_queue<int, vector<int>, less<int> > que;
        
        for(int i=0;i<n;i++){
            scanf("%lld", &val);
            if(m.find(val) == m.end()){
                m[val] = 1;
            }else{
                m[val]++;
            }
        }
        
        for(map<LL, int>::iterator it = m.begin(); it != m.end(); it++){
            que.push(it->second);
        }
        
        int ans = 0;
        while(que.size() >= 3){
            ans++;
            int one = que.top(); que.pop();
            int two = que.top(); que.pop();
            int three = que.top(); que.pop();
            one--;
            two--;
            three--;
            
            if(one){
                 que.push(one);
            } 
            if(two){
                 que.push(two);
            } 
            if(three){
                 que.push(three);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
