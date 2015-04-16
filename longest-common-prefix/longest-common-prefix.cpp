/*************************************************************************
  > File Name: longest-common-prefix.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月16日 12:51:15
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
    string longestCommonPrefix(vector<string>& strs) {
        int vecSize = strs.size();
        if(vecSize == 0){
            return "";
        }

        string& first = strs[0];
        int ans = first.length();
        int strSize = 0;

        for(int i=1; i< vecSize; i++){
            string& str = strs[i];
            strSize = str.length();
            if(strSize < ans){
                ans = strSize;
            }
            for(int j=0;j<ans;j++){
                if(str[j] != first[j]){
                    ans = j;
                    break;
                }
            }
            if(ans == 0){
                return "";
            }
        }
        return first.substr(0,ans);
    }
};

void output(vector<string>&vec){
    printf("vec.size = %d\n", vec.size());
    for(int i=0;i<vec.size();i++){
        printf("\t%s\n",vec[i].c_str());
    }
}

void test(){
    Solution work;

    vector<string> vec;
    string ans;

    ans = work.longestCommonPrefix(vec);
    output(vec);
    printf("ans = %s\n", ans.c_str());

    vec.push_back("1234");
    ans = work.longestCommonPrefix(vec);
    output(vec);
    printf("ans = %s\n", ans.c_str());
    
    vec.push_back("1254");
    vec.push_back("1274");
    ans = work.longestCommonPrefix(vec);
    output(vec);
    printf("ans = %s\n", ans.c_str());
    
    vec.push_back("1234");
    vec.push_back("4234");

    ans = work.longestCommonPrefix(vec);
    output(vec);
    printf("ans = %s\n", ans.c_str());

}


int main() {
    test();
    return 0;
}
