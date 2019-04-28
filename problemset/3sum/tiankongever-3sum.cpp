/*************************************************************************
  > File Name: 3sum.cpp
  > Author: tiankongever(skyyuan)
  > Mail: i@tiankongever.com 
  > Created Time: 2015年05月21日 星期四 01时05分39秒
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
    map<int,int>m;//<val, times>
    set<pair<int,int>>s;
    vector<vector<int>>ans;
    void addAns(int a, int b, int c){
        vector<int>line;
        if(s.find(make_pair(a,b)) == s.end()){
            s.insert(make_pair(a,b));
            line.push_back(a);
            line.push_back(b);
            line.push_back(c);
            ans.push_back(line);
        }

    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int a,b,c;
        m.clear();
        s.clear();
        ans.clear();

        for(int i=0;i<nums.size();i++){
            if(m.find(nums[i]) == m.end()){
                m[nums[i]] = 1;
            }else{
                m[nums[i]] = m[nums[i]] + 1;
            }
        }

        for(map<int,int>::iterator i=m.begin(); i != m.end();i++){
            for(map<int,int>::iterator j = i; j != m.end(); j++){
                if(i == j && i->second == 1){
                    continue;
                }
                a = i->first;
                b = j->first;
                c = - (a + b);
                if(!(a<= b && b <= c)){
                    continue;
                }
                if(m.find(c) == m.end()){
                    continue;
                }
                if(c == a && c == b){
                    if(m[c] > 2){
                        addAns(a,b,c);
                    }    
                }else if(c == a || c == b){
                    if(m[c] > 1){
                        addAns(a,b,c);
                    }
                }else{
                    addAns(a,b,c); 
                }

            }
        }

        return ans;
    }
};

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


void test(vector<int>&data){
    Solution work;
    vector<vector<int>>ans;
    ans = work.threeSum(data);
    
    output("data", data);
    output("ans", ans);
}

int main() {
    vector<int>data;

    data = {-1,0,1,2,-1,-4};
    test(data);

    data = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
    test(data);

    return 0;
}
