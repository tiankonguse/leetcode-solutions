/*************************************************************************
    > File Name: bitwise-and-of-numbers-range.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月26日 星期日 12时33分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;

typedef long long ll;
class Solution {
    void swap(ll&a, ll&b){
        ll tmp = a;
        a = b;
        b = tmp;
    }
    ll getNext(ll a){
        return a & (a - 1);
    }

    ll getPre(ll a){
        return (a | (a ^ (a-1))) + 1;
    }
public:
    int rangeBitwiseAnd(int _m, int _n) {
        ll m = _m;
        ll n = _n;
        ll tmp;
        if(m >= n){
            swap(m, n);
        }
        ll ans = m & n;
        ll next;
        ll pre;

        if(ans == 0){
            return 0;
        }

        next = n;
        while(getNext(next) >= m){
            next = getNext(next);
            ans &= next;
            if(ans == 0){
                return 0;
            }
        }
        
        pre = m;
        while(getPre(pre) <= next){
            pre = getPre(pre);
            ans &= pre;
            if(ans == 0){
                return 0;
            }
        }
        return ans;
    }
};


void test(){
    srand(time(NULL));
    Solution work;

    int n,m;
    int ans;

    n=0;
    m=0;
    ans = work.rangeBitwiseAnd(n,m);
    printf("ans=%d n=%d m=%d\n",ans,n,m);

    n=0;
    m=10;
    ans = work.rangeBitwiseAnd(n,m);
    printf("ans=%d n=%d m=%d\n",ans,n,m);
    
    n=9;
    m=10;
    ans = work.rangeBitwiseAnd(n,m);
    printf("ans=%d n=%d m=%d\n",ans,n,m);
    
    n=10;
    m=10;
    ans = work.rangeBitwiseAnd(n,m);
    printf("ans=%d n=%d m=%d\n",ans,n,m);
    
    n=5;
    m=7;
    ans = work.rangeBitwiseAnd(n,m);
    printf("ans=%d n=%d m=%d\n",ans,n,m);
}

int main(){
    test();
    return 0;
}
