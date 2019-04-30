/*************************************************************************
  > File Name: letter-combinations-of-a-phone-number.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年05月21日 20:42:13
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
    vector<string>digitMap;
public:
    Solution(){
        digitMap.clear();
        digitMap.push_back("");//0
        digitMap.push_back("");//1
        digitMap.push_back("abc");//2
        digitMap.push_back("def");//3
        digitMap.push_back("ghi");//4
        digitMap.push_back("jkl");//5
        digitMap.push_back("mno");//6
        digitMap.push_back("pqrs");//7
        digitMap.push_back("tuv");//8
        digitMap.push_back("wxyz");//9
    }
    vector<string> letterCombinations(string digits) {
        queue<string>que;
        que.push("");
        vector<string>ans;
        int digitsLen = digits.length();

        if(digitsLen == 0){
            return ans;
        }
        int d = 0;
        int l = 0;
        string tmp;
        for(int i=0;i<digitsLen;i++){
            d = digits[i] - '0';
            string& s = digitMap[d];
            int queSize = que.size();
            if(d >= 2 && d <= 9){
                while(queSize>0){
                    queSize = queSize - 1;

                    tmp = que.front();
                    que.pop();
                    
                    int tmpSize = tmp.size();
                    tmp.append(" ");
                   
                    for(int i=0;i<s.size();i++){
                        tmp[tmpSize] = s[i]; 
                        que.push(tmp);
                    }

                }
            }        
        }
        while(!que.empty()){
            ans.push_back(que.front());
            que.pop();
        }
        return ans;
    }
};
int main() {
    Solution work;

    string data;
    vector<string>ans;

    data = "23";
    printf("data : %s\n", data.c_str());
    ans = work.letterCombinations(data);
    printf("ans : %d\n", ans.size());
    for(int i=0;i<ans.size();i++){
        printf("\t%s\n",ans[i].c_str());
    }


    return 0;
}
