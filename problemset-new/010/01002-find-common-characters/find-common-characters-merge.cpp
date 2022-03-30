/*************************************************************************
    > File Name: find-common-characters.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月 8日 21:17:32
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
    string mergeTwoString(string& first, string& second) {
        vector<int> secondCount(26, 0);
        vector<int> fiirstCount(26, 0);

        for(int j=0; j<first.size(); j++) {
            fiirstCount[first[j] - 'a']++;
        }
        for(int j=0; j<second.size(); j++) {
            secondCount[second[j] - 'a']++;
        }

        string ans;
        for(char j='a'; j<='z'; j++) {
            int num = min(fiirstCount[j - 'a'], secondCount[j - 'a']);
            while(num > 0) {
                num--;
                ans.push_back(j);
            }
        }
        return ans;
    }
    vector<string> split(string& first) {
        vector<string> ans;
        string tmpStr = "a";
        for(int j=0; j<first.size(); j++) {
            tmpStr[0]=first[j];
            ans.push_back(tmpStr);
        }
        return ans;
    }
public:
    vector<string> commonChars(vector<string>& A) {
        string ans = mergeTwoString(A[0], A[0]);
        for(int i=1; i<A.size(); i++) {
            ans = mergeTwoString(ans, A[i]);
        }
        return split(ans);
    }
};

template <class ansType, class dataType>
void test(dataType& data, ansType& expectAns) {
    Solution work;
    ansType ans;
    ans = work.commonChars(data);

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
    vector<string> data;
    vector<string> expectAns;

    data = {"bella","label","roller"};
    expectAns = {"e","l","l"};
    test(data, expectAns);

    data = {"cool","lock","cook"};
    expectAns = {"c","o"};
    test(data, expectAns);
    return 0;
}
