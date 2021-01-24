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
public:
    vector<string> commonChars(vector<string>& data) {
        vector<int> countChar;
        vector<int> tmpCount;
        countChar.resize(26, 0);
        tmpCount.resize(26, 0);
        for(int i=0; i<data.size(); i++) {
            string& one = data[i];
            tmpCount.clear();
            tmpCount.resize(26, 0);
            for(int j=0; j<one.size(); j++) {
                tmpCount[one[j] - 'a']++;
            }

            if(i == 0) {
                countChar = tmpCount;
                continue;
            }
            for(int j='a'; j<='z'; j++) {
                countChar[j - 'a'] = min(countChar[j - 'a'], tmpCount[j - 'a']);
            }
        }

        vector<string> ans;
        string tmpStr = "a";
        for(int j='a'; j<='z'; j++) {
            tmpStr[0] = j;
            while(countChar[j - 'a'] > 0) {
                ans.push_back(tmpStr);
                countChar[j - 'a']--;
            }
        }

        return ans;
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
    if(!check){
        printf("index %d: NO\n", index);
        output("data", data);
        output("ans", ans);
        output("expectAns", expectAns);
    }else{
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
