/*************************************************************************
    > File Name: longest-consecutive-sequence.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月21日 星期二 23时41分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;


/*
 * fuck problem : map in O(n log(n))  complexity.  
 */
class Solution {
    int solver(vector<int>&vec){
        if(vec.size() == 0){
            return 0;
        }
        set<int> s(vec.begin(), vec.end());
        int pre = *(s.begin()) - 1;
        int nowAns = 0;
        int ans = 0;
        int nowVal;

        for(set<int>::iterator it = s.begin(); it != s.end(); it++){
            nowVal = *it;
            if(nowVal == pre + 1){
                nowAns = nowAns + 1;
            }else{
                if(nowAns > ans){
                    ans = nowAns;
                }
                nowAns = 1;
            }
            pre = nowVal;
        }

        if(nowAns > ans){
            ans = nowAns;
        }
        
        return ans;
    }
public:
    int longestConsecutive(vector<int> &num) {
        int ans = 0;
        ans = solver(num);
        return ans;
    }
};

void output(vector<int>& vec){
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++){
        printf("%d ", *it);
    }
    printf("\n");
}

void test(){
    srand(time(NULL));
    Solution work;

    vector<int>vec;
    int ans;

    vec = {100, 4, 200, 1, 3, 2};
    output(vec);
    ans = work.longestConsecutive(vec);
    printf("ans = %d\n", ans);

    vec = {5, 4, 6, 1, 3, 2};
    output(vec);
    ans = work.longestConsecutive(vec);
    printf("ans = %d\n", ans);
}

int main(){
    test();
    return 0;
}
