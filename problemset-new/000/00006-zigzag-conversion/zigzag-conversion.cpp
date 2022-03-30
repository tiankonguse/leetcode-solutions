/*************************************************************************
    > File Name: zigzag-conversion.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 20时02分30秒
 ************************************************************************/

#include<stdio.h>
#include<string>
using namespace std;

class Solution {
public:
    string convert(string s, int nRows) {
       if(nRows == 1){
           return s;
       }
        
        int length = s.length();
        char* ans = new char[length+1];
        int step = 2 * nRows - 2;
        int K = step;
        int line = 1;
        int next;
        
        int start = 0;
        ans[length] = '\0';

        //first line  
        for(int i = line; i <= length; i += step){
            ans[start++] = s[i - 1];
        }

        //middle line
        for(line++, K -= 2; line < nRows; line++, K -= 2){
            for(int i = line; i <= length; i += step){
                ans[start++] = s[i - 1];

                if(i + K <= length){
                    ans[start++] = s[i + K - 1];
                }
            }
        }

        //last line
        for(int i = line; i<= length; i += step){
            ans[start++] =  s[i - 1 ];
        }
        ans[start++] = '\0';


        string o = ans;
        delete[] ans;

        return o;

    }
};

void test(){
    Solution work;
    string ans;
    string input;

    input = "PAYPALISHIRING";
    ans = work.convert(input, 3);
    printf("input=%s\nans=%s\n", input.c_str(), ans.c_str());


    input = "PAYPALISHIRING";
    ans = work.convert(input, 2);
    printf("input=%s\nans=%s\n", input.c_str(), ans.c_str());



    input = "PAYPALISHIRING";
    ans = work.convert(input, 22);
    printf("input=%s\nans=%s\n", input.c_str(), ans.c_str());

    input = "A";
    ans = work.convert(input, 1);
    printf("input=%s\nans=%s\n", input.c_str(), ans.c_str());
}

int main(){
    test();
    return 0;
}
