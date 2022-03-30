/*************************************************************************
    > File Name: string-to-integer-atoi.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月17日 星期五 00时58分49秒
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

class Solution {
    long long min;
    long long max;
public:
    Solution(){
        min = 2147483648;
        max = 2147483647;
    }
    bool isdigit(char c){
        if(c>='0' && c <= '9'){
            return true;
        }else{
            return false;
        }
    }
    bool isspace(char c){
        switch(c){
            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\f':
            case '\r':
                return true;
            default:
                return false;
        }
    }
    int myAtoi(string str) {
        long long ans = 0;
        int size = str.length();
        int pos = 0;
        int sign = 1;

        for(; pos < size; pos++){
            if(!isspace(str[pos])){
                break;
            }
        }

        if(pos == size){
            return 0;
        }
    
        if(str[pos] == '+'){
            sign = 1;
            pos = pos + 1;
        }else if(str[pos] == '-'){
            sign = -1;
            pos = pos + 1;
        }

        for(; pos < size; pos++){
            if(isdigit(str[pos])){
                ans = ans * 10 + (str[pos] - '0');
                if(ans * sign <= -min){
                    ans = min;
                    break;
                }else if(ans * sign >= max){
                    ans = max;
                    break;
                }
            }else{
                break;
            }
        }
        return ans*sign;
    }
};
void test(){
    srand(time(NULL));
    Solution work;
    string str;
    int ans;

    str="";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);
    

    str="1";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);
    
    
    str="01";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);
    
    str="09";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" +7";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" + 7";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" + -";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" -07";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 2147483647";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" -2147483648";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" -3147483648";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 2147483648";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 2147483sdad648";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 9223372036854775807";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 9223372036854775808";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 9223372036854775809";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" 9223372036854775819";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" -9223372036854775808";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

    str=" -9223372036854775809";
    ans = work.myAtoi(str);
    printf("str=%s ans=%d\n", str.c_str(), ans);

}

int main(){
    test();
    return 0;
}
