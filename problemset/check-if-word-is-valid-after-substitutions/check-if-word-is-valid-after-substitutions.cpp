/*************************************************************************
    > File Name: check-if-word-is-valid-after-substitutions.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月 8日 22:04:22
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;



class Solution {
public:
    bool isValid(string& data) {
        stack<char> sta;
        for(int i=0; i<data.size(); i++) {
            sta.push(data[i]);
            while(sta.size() > 0 && sta.top() == 'c') {
                if(sta.size() < 3) {
                    return false;
                }
                char c = sta.top();
                sta.pop();
                char b = sta.top();
                sta.pop();
                char a = sta.top();
                sta.pop();
                if(c != 'c' || b != 'b' || a != 'a') {
                    return false;
                }
            }
        }
        if(sta.size() != 0) {
            return false;
        }
        return true;
    }
};

template <class ansType, class dataType>
void test(dataType& data, ansType& expectAns) {
    Solution work;
    ansType ans;
    ans = work.isValid(data);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("data", data);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }

}

int main() {
    string data;
    bool expectAns;

    data = "aabcbc";
    expectAns = true;
    test(data, expectAns);

    data = "abcabcababcc";
    expectAns = true;
    test(data, expectAns);


    data = "abccba";
    expectAns = false;
    test(data, expectAns);

    data = "cababc";
    expectAns = false;
    test(data, expectAns);


    return 0;
}
