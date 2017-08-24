/*************************************************************************
  > File Name: permutation-sequence.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 13:50 2017/8/23
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
    
    vector<int> factorial;
    vector<int> nums;
    void init(int n){
        factorial.clear();
        factorial.push_back(1);
        for(int i=1;i<=9;i++){
            factorial.push_back(i*factorial[i-1]);
        }
        
        nums.clear();
        nums.push_back(0);
        for(int i=1;i<=n;i++){
            nums.push_back(i);
        }
    }
    
    void backVector(int pos, int n){
        for(int i = pos; i< n;i++){
            nums[i] = nums[i + 1];
        }
    }
    
public:
    string getPermutation(int n, int k) {
        string ans;
        init(n);
        
        int pos;
        for(int i=n; i > 0;i--){
            pos = (k - 1)/factorial[i-1] + 1;
            ans.push_back(nums[pos] + '0');
            backVector(pos, i);
            k -= (pos - 1) * factorial[i-1];
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


void test(int n, int k){
    Solution work;
    string ans;
    output("n", n);
    output("k", k);
    ans = work.getPermutation(n,  k);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {1,2,3};
    test(nums);


    return 0;
}
