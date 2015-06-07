/*************************************************************************
    > File Name: count-primes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年05月06日 星期三 23时48分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<math.h>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;


const int N=1000000;
const int M=300000;
class Solution {
    bool is[N];
    int prm[M];
    int prmNum;
    public:
    Solution(){
        prmNum = getprm(); 
    }
    int getprm() {
        int e = (int)(sqrt(0.0 + N) + 1),k=0,i;
        memset(is, 1, sizeof(is));
        prm[k++] = 2;
        is[0] = is[1] = 0;
        for (i = 4; i < N; i += 2) is[i] = 0;
        for(i=3; i<e; i+=2) {
            if(is[i]) {
                prm[k++]=i;
                for(int s=i+i,j=i*i; j<N; j+=s)is[j]=0;
            }
        }
        for (; i < N; i += 2)
            if (is[i])prm[k++] = i;
        return k;
    }
    bool isPrm(int n){
        int e = (int)(sqrt(0.0 + n) + 1);
        for(int i=0;i<prmNum;i++){
            if(n % prm[i] == 0){
                return false;
            }
            if(prm[i] > e){
                break;
            }

        } 

        return true;
    }
    void addPrm(int n, int&ans){
        int e = (int)(sqrt(0.0 + n) + 1);
        for(int i=N;i<n;i++){
            if(isPrm(i)){
                ans = ans + 1;
            }
        }
    }
    int countPrimes(int n) {

        int ans = 0;
        int i=0;
        for(i=0;i<prmNum;i++){
            if(prm[i] < n){
                ans++;
            }else{
                break;
            }
        }
        if(i == prmNum){
            addPrm(n, ans);
        }
        return ans;
    }
};

void test(){
    srand(time(NULL));
    Solution work;
    int ans,n;

    n = 10;
    ans = work.countPrimes(n);
    printf("prm(%d) = %d\n", n, ans);

    n = 2;
    ans = work.countPrimes(n);
    printf("prm(%d) = %d\n", n, ans);

    n = 1500000;
    ans = work.countPrimes(n);
    printf("prm(%d) = %d\n", n, ans);
}

int main(){
    test();
    return 0;
}
