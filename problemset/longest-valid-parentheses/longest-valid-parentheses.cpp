/*************************************************************************
  > File Name: longest-valid-parentheses.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 22:50 2017/8/22
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

class Solution {
public:
    int longestValidParentheses(string& s) {
        int ans = 0;
        vector<int> vec;
        
        int nowAns = 0;
        int valid = 1;
        
        vec.push_back(0);
        for(int i=0; i<s.length(); i++){
            if(s[i] == '('){
                vec.push_back(-1);
                vec.push_back(0);
            }else{
                if(vec.size() == 1){
                    //说明这个右括号没有左括号相匹配
                    vec.pop_back();
                    vec.push_back(0);
                }else{
                    //说明可以匹配上, 至少有三个, 格式为  num1 ( num2 
                    nowAns = vec.back() + 2;
                    vec.pop_back(); //num2
                    
                    vec.pop_back(); // -1
                    
                    nowAns += vec.back();
                    vec.pop_back(); //num1
                    
                    vec.push_back(nowAns);
                    if(nowAns > ans){
                        ans = nowAns;
                    }
                }
            }
        }
        return ans;
    }
};

void output(char const* name, std::string &data){
    printf("%s:\n   %s\n", name, data.c_str());
    printf("\n");
}

void output(char const* name, int data){
    printf("%s:\n    %d\n", name, data);
    printf("\n");
}

void output(char const* name, vector<int>&data){
    printf("%s:", name);
    for(int i=0;i<data.size();i++){
        printf("%d ", data[i]);
    }
    printf("\n");
}

void output(char const* name, vector<vector<int>>&data){
    printf("%s:\n", name);
    for(int i=0;i<data.size();i++){
        output("    ", data[i]);
    }
    printf("\n");
}


void test(string& data){
    Solution work;
    int ans;
    ans = work.longestValidParentheses(data);
    
    output("data", data);
    output("ans", ans);
}

int main() {
    string data;

    data = "(()";
    test(data);

    data = ")()())";
    test(data);

    return 0;
}
