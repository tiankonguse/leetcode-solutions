/*************************************************************************
  > File Name: remove-element.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com
  > Created Time: 2015年05月21日 星期四 22时33分16秒
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
#include "../../include/base.h"
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        for(int i=0;i<n;i++){
            if(nums[i] == val){
                nums[i] = nums[n - 1];
                n--;
                i--;
            }
        }
        return n;
    }
};


template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.removeElement(firstData, secondData);

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

    vector<int>first;
    int second;
    int expectAns;
    Solution work;

    first = {3,2,2,3};
    second = 3;
    expectAns = 2;
    test(expectAns, first, second);

    first = {0,1,2,2,3,0,4,2};
    second = 2;
    expectAns = 5;
    test(expectAns, first, second);

    first = {0,0};
    second = 0;
    expectAns = 0;
    test(expectAns, first, second);
    return 0;
}
