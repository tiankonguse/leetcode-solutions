/*************************************************************************
    > File Name: pascals-triangle.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 00:31:00 2019
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
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        if(numRows == 0) {
            return ans;
        }

        vector<int> row;
        row.push_back(1);
        ans.push_back(row);
        for(int i=1; i<numRows; i++) {
            vector<int> row;
            row.push_back(1);

            vector<int>& lastRow = ans[ans.size() - 1];
            for(int i=1; i<lastRow.size(); i++) {
                row.push_back(lastRow[i-1] + lastRow[i]);
            }
            row.push_back(1);
            ans.push_back(row);
        }
        return ans;
    }
};
template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& data, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.generate(data);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("data", data);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    int data;
    vector<vector<int>> expectAns;


    data = 5;
    expectAns = {
        {1},
        {1,1},
        {1,2,1},
        {1,3,3,1},
        {1,4,6,4,1}
    };
    test(expectAns, data);



    return 0;
}

