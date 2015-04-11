/*************************************************************************
    > File Name: evaluate-reverse-polish-notation.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月11日 星期六 19时29分40秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<stack>
#include<stdlib.h>
using namespace std;


class Solution {
    int debug;
public:
    Solution(int debug=0):debug(debug){

    }
    int evalRPN(vector<string> &tokens) {
        stack<int>sta;
        int ans = 0;

        int first, second, result;

        for(int i=0;i<tokens.size();i++){
            if(tokens[i].size() > 1){
                    result = atoi(tokens[i].c_str());
                    sta.push(result);
                    if(debug){
                        printf("%d \n", result);
                    }
                    continue;
            }
            switch(tokens[i][0]){
                case '+':
                    second = sta.top();sta.pop();
                    first = sta.top();sta.pop();
                    result = first + second;
                    sta.push(result);
                    if(debug){
                        printf("%d %s %d = %d\n", first, tokens[i].c_str(), second, result);
                    }
                    break;
                case '-':
                    second = sta.top();sta.pop();
                    first = sta.top();sta.pop();
                    result = first - second;
                    sta.push(result);
                    if(debug){
                        printf("%d %s %d = %d\n", first, tokens[i].c_str(), second, result);
                    }
                    break;
                case '*':
                    second = sta.top();sta.pop();
                    first = sta.top();sta.pop();
                    result = first * second;
                    sta.push(result);
                    if(debug){
                        printf("%d %s %d = %d\n", first, tokens[i].c_str(), second, result);
                    }
                    break;
                case '/':
                    second = sta.top();sta.pop();
                    first = sta.top();sta.pop();
                    result = first / second;
                    sta.push(result);
                    if(debug){
                        printf("%d %s %d = %d\n", first, tokens[i].c_str(), second, result);
                    }
                    break;
                default:
                    result = atoi(tokens[i].c_str());
                    sta.push(result);
                    if(debug){
                        printf("%d \n", result);
                    }
            }
        }
        if(!sta.empty()){
            ans = sta.top();
        }

        return ans;
    }
};

void test(){
    Solution work(1);
    vector<string>str;
    int ans, realAns;


    //["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9/
    str.clear();
    str.push_back("2");
    str.push_back("1");
    str.push_back("+");
    str.push_back("3");
    str.push_back("*");
    ans = work.evalRPN(str);
    realAns = 9;
    printf("ans=%d %s\n", ans, ans==realAns?"YES":"NO");
    str.clear();


    //["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
    str.clear();
    str.push_back("4");
    str.push_back("13");
    str.push_back("5");
    str.push_back("/");
    str.push_back("+");
    ans = work.evalRPN(str);
    realAns = 6;
    printf("ans=%d %s\n", ans, ans==realAns?"YES":"NO");
    str.clear();

    //["-1","1","*","-1","+"]
    str.clear();
    str.push_back("-1");
    str.push_back("1");
    str.push_back("*");
    str.push_back("-1");
    str.push_back("+");
    ans = work.evalRPN(str);
    realAns = -2;
    printf("ans=%d %s\n", ans, ans==realAns?"YES":"NO");
    str.clear();
}

int main(){
    test();
    return 0;
}
