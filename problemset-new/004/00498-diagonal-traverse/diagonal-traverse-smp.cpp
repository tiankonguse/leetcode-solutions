/*************************************************************************
    > File Name: diagonal-traverse-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 00:45:37 2019
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
    int n,m,dir;
    vector<int> ans;
    void run(int x, int y, vector<vector<int>>& matrix) {
        vector<int> tmpLine;
        while(x >= 0 && x < n && y >= 0 && y < m) {
            tmpLine.push_back(matrix[x][y]);
            x++,y--;
        }
        if(dir == 1) {
            ans.insert(ans.end(), tmpLine.rbegin(), tmpLine.rend());
        } else {
            ans.insert(ans.end(), tmpLine.begin(), tmpLine.end());
        }
        dir = -dir;
    }
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        n = matrix.size();
        if(n == 0) {
            return ans;
        }
        m = matrix[0].size();
        dir = 1;
        //x=0, y: 0 => m-1
        for(int i=0; i<m; i++) {
            run(0, i, matrix);
        }
        //y=m-1, x: 1 => n-1
        for(int i = 1; i<n; i++) {
            run(i, m-1, matrix);
        }
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& data, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.findDiagonalOrder(data);

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
    vector<vector<int>> data;
    vector<int> expectAns;


    data = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    expectAns = {1,2,4,7,5,3,6,8,9};
    test(expectAns, data);


    data = {
        { 1 }
    };
    expectAns = {1};
    test(expectAns, data);

    data = {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };
    expectAns = {1,2,4,5,3,6};
    test(expectAns, data);

    data = {
        { 1, 2 },
        { 4, 5 },
        { 7, 8}
    };
    expectAns = {1,2,4,7,5,8};
    test(expectAns, data);

    return 0;
}
