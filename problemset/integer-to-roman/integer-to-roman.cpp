/*************************************************************************
> File Name: integer-to-roman.cpp
> Author: tiankonguse(skyyuan)
> Mail: i@tiankonguse.com 
> Created Time: 2015年05月21日 星期四 00时08分43秒
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
    string intToRoman(int num) {
        string ans = "";
        
        while(num){
            if(num >= 1000){
                ans.append("M");
                num = num - 1000;
                continue;
            }
            if(num >= 900){
                ans.append("CM");
                num = num - 900;
                continue;
            }
            if(num >= 500){
                ans.append("D");
                num = num - 500;
                continue;
            }
            if(num >= 400){
               ans.append("CD");
                num = num - 400;
                continue;
            }
            if(num >= 100){
                ans.append("C");
                num = num - 100;
                continue;
            }
            if(num >= 90){
                ans.append("XC");
                num = num - 90;
                continue;
            }
            if(num >= 50){
                ans.append("L");
                num = num - 50;
                continue;
            }
            if(num >= 40){
                ans.append("XL");
                num = num - 40;
                continue;
            }
            if(num >= 10){
                ans.append("X");
                num = num - 10;
                continue;
            }
            if(num >= 9){
                ans.append("IX");
                num = num - 9;
                continue;
            }
            if(num >= 5){
                ans.append("V");
                num = num - 5;
                continue;
            }
            if(num >= 4){
                ans.append("IV");
                num = num - 4;
                continue;
            }
            if(num >= 1){
                ans.append("I");
                num = num - 1;
                continue;
            }
            

        }
        
        return ans;
    }
};

void test(int num, char const* ans){
    string testAns;
    Solution work;
    testAns = work.intToRoman(num);
    if(strcmp(ans, testAns.c_str())){
        printf("num=%d output=%s ans=%s %s\n", num, testAns.c_str(), ans, strcmp(ans, testAns.c_str())==0?"YES":"NO");
    
    }
}


int main() {
    

test(3998,"MMMCMXCVIII");
test(3999,"MMMCMXCIX");
    return 0;
}
