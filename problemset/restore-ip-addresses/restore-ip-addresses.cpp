/*************************************************************************
    > File Name: restore-ip-addresses.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月17日 星期五 00时18分07秒
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
    vector<string>ans;
    struct IP{
        int array[4];
        string toString(){
            char buf[64];
            snprintf(buf, sizeof(buf), "%d.%d.%d.%d", array[0], array[1], array[2], array[3]);
            return buf;
        }
        IP(){
            memset(array, 0, sizeof(array));
        }
        void set(int lev, int val){
            array[lev] = val;
        }
    };
    struct IP ip;
    string str;
    int maxPos;
    const int maxLev;

    bool ok(int val){
        if(val >=0 && val <=255){
            return true;
        }else{
            return false;
        }
    }

    void dfs(int lev, int pos){
        if(pos == maxPos){
            if(lev == maxLev){
                ans.push_back(ip.toString());
            }
            return ;
        }
        if(lev == maxLev){
            return ;
        }

        int now = 0;

        if(pos < maxPos){
            now = str[pos] - '0';
            if(ok(now)){
                ip.set(lev, now);
                dfs(lev+1, pos+1);
            }else{
                return;
            }
        }

        pos = pos + 1; 
        if(now > 0 && pos < maxPos){
            now = now * 10 + (str[pos] - '0');
            if(ok(now)){
                ip.set(lev, now);
                dfs(lev+1, pos+1);
            }else{
                return ;
            }
        }

        
        pos = pos + 1;
        if(now > 0 && pos < maxPos){
            now = now * 10 + (str[pos] - '0');
            if(ok(now)){
                ip.set(lev, now);
                dfs(lev+1, pos+1);
            }else{
                return ;
            }
        }

    }

public:

    Solution():maxLev(4){

    }

    vector<string> restoreIpAddresses(string s) {
        ans.clear();
        str = s;
        maxPos = s.length();

        if(maxPos == 0){
            return ans;
        }

        dfs(0,0);

        return ans;
    }
};
void output(vector<string>&ans){
    printf("ans size = %d\n",(int)ans.size());
    for(int i=0;i<ans.size();i++){
        printf("\t%s\n",ans[i].c_str());
    }
    printf("\n");
}


void test(){
    srand(time(NULL));
    Solution work;
    
    vector<string>ans;
    string s;

    s="";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);


    s="33";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);

    s="3893";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);


    s="25525511135";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);


    s="2550035";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);

    s="0000";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);

    s="255255255255";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);

    s="00000";
    ans = work.restoreIpAddresses(s);
    printf("s=%s\n", s.c_str());
    output(ans);

    s="255255255255";
}

int main(){
    test();
    return 0;
}
