/*************************************************************************
    > File Name: excel-sheet-column-title.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 23时55分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>
#include<time.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    string convertToTitle(int n) {
        string ans = "";
        ll onebase = 1;
        ll onemax = 26;
        ll num = 0;
        while(n > onemax){
            onebase = onebase * 26;
            onemax = onemax + 26 * onebase;
            num++;
        }
        
        ll c = 1;
        ll left;
        while(num >= 0){
            if(num == 0){
                ans += ('A' + n - 1);
                 break;
            }
            c = n / onebase;
            if(n % onebase == 0){
                 c--;
                left = n - c * onebase;
                if(left > onebase){
                    c++;
                }
            }
            ans += ('A' + c - 1);
            n = n - c * onebase;
            onebase /= 26;
            num--;
        }
        return ans;
    }
};

void test(){
    srand(time(NULL));
    Solution work;

    int data;
    string ans;
    
    for(int i=1;i<=53;i++){
        data = i;
        ans = work.convertToTitle(data);
        printf("data=%d ans=%s\n", data, ans.c_str());
    }

    data = 702;
    ans = work.convertToTitle(data);
    printf("data=%d ans=%s\n", data, ans.c_str());
    
    data = 703;
    ans = work.convertToTitle(data);
    printf("data=%d ans=%s\n", data, ans.c_str());
    
    data = 1000000001;
    ans = work.convertToTitle(data);
    printf("data=%d ans=%s\n", data, ans.c_str());
}

int main(){
    test();
    return 0;
}
