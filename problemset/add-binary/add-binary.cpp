/*************************************************************************
    > File Name: add-binary.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > link: https://leetcode.com/problems/add-binary/
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
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();

class Solution {
public:
    string addBinary(string first, string second) {
        string ans;

        //计算最大长度+1（考虑进位）
        int maxLen = max(first.length(),second.length()) + 1;
        //翻转
        std::reverse(first.begin(), first.end());
        std::reverse(second.begin(), second.end());
        //高位补零
        first.resize(maxLen, '0');
        second.resize(maxLen, '0');
        //计算答案
        int sum = 0;
        const int base = 2;
        for(int i=0; i<maxLen; i++) {
            sum += (first[i] - '0') + (second[i] - '0');
            ans.push_back('0' + (sum % base));
            sum /= base;
        }
        //去掉高位多于的0
        while(ans.length() > 1 && ans[ans.length() - 1] == '0') {
            ans.pop_back();
        }
        //翻转答案
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.addBinary(firstData, secondData);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("firstData", firstData);
        output("secondData", secondData);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    string first;
    string second;
    string expectAns;


    first = "11";
    second = "1";
    expectAns = "100";
    test(expectAns, first, second);


    first = "1010";
    second = "1011";
    expectAns = "10101";
    test(expectAns, first, second);



    first = "0010";
    second = "0001";
    expectAns = "11";
    test(expectAns, first, second);

    return 0;
}

