/*************************************************************************
    > File Name: longest-palindromic-substring.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月21日 星期二 22时08分25秒
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
    int getMaxEdge(int center, string& s){
        int len = s.length();
        int ans = 0;
        int l,r;

        while(1){
            ans = ans + 1;
            l = center - ans;
            r = center + ans;
            if(l >= 0  && r < len && s[l] == s[r]){
                continue;
            }else{
                ans = ans - 1;
                return ans;
            }
        }
        return ans;
    }

    int getMaxEdge(int l, int r, string& s){
        int len = s.length();
        int ans = 0;

        while(1){
            ans = ans + 1;
            if(l >= 0  && r < len && s[l] == s[r]){
                l--,r++;
                continue;
            }else{
                ans = ans - 1;
                return ans;
            }
        }
        return ans;
    }
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if(len == 0){
            return s;
        }
        int nowCenter=0, nowEdge=0, nowAns = 1, nowl = 0, nowr = 0; 
        int maxl = nowl;
        int maxr = nowr;
        int maxAns = 1;
        
        for(int i=0; i<len;i++){
            nowEdge = getMaxEdge(i, s);
            nowAns = 1 + nowEdge * 2;
            nowl = i - nowEdge;
            nowr = i + nowEdge;

            if(nowAns > maxAns){
                maxl = nowl;
                maxr = nowr;
                maxAns = nowAns;
            }
        }
       
        for(int i=0;i<len-1;i++){
            nowEdge = getMaxEdge(i, i+1, s);
            nowAns = nowEdge * 2;
            nowl = i + 1 - nowEdge;
            nowr = i + nowEdge;
            if(nowAns > maxAns){
                maxl = nowl;
                maxr = nowr;
                maxAns = nowAns;
            }
        }
        
        string ans = s.substr(maxl, maxAns);
        return ans;
    }
};

void test(){
    srand(time(NULL));
    Solution work;

    string data;
    string ans;

    data = "1234554321";
    printf("data=%s\n",data.c_str());
    ans = work.longestPalindrome(data);
    printf("ans=%s\n",ans.c_str());


    data = "";
    printf("data=%s\n",data.c_str());
    ans = work.longestPalindrome(data);
    printf("ans=%s\n",ans.c_str());


    data = "1";
    printf("data=%s\n",data.c_str());
    ans = work.longestPalindrome(data);
    printf("ans=%s\n",ans.c_str());

    data = "122111233211123454321";
    printf("data=%s\n",data.c_str());
    ans = work.longestPalindrome(data);
    printf("ans=%s\n",ans.c_str());
}

int main(){
    test();
    return 0;
}
