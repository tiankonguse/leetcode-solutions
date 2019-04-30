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


class Solution {
public:
    string convertToTitle(int n) {
        string ans = "";
        vector<int>base;
        vector<int>max;
        base.push_back(1);
        max.push_back(26);
        int onebase;
        int onemax;
        onemax = max[max.size() - 1];
        while(n > onemax){
            onebase = base[base.size() - 1] * 26;
            onemax = onemax + 26 * onebase;
            max.push_back(onemax);
            base.push_back(onebase);
        }
        
        int c = 1;
        int num = base.size() - 1;
        int left;
        printf("num=%d\n",num);
        while(num >= 0){
            if(num == 0){
                ans += ('A' + n - 1);
                break;
            }
            c = n / base[num];
            if(n % base[num] == 0){
                c--;
                left = n - c * base[num];
                printf("n=%d b=%d c=%d left=%d\n", n, base[num], c, left);
                if(left > base[num-1]*26){
                    c++;
                }
            }
            ans += ('A' + c - 1);
            n = n - c * base[num];
            printf("base=%d c=%d n=%d\n", base[num], c,n);
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
}

int main(){
    test();
    return 0;
}
