/*************************************************************************
    > File Name: two-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月12日 星期日 02时09分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;

void printfVec(vector<int> vec){
    printf("\t");
    for(int i=0;i<vec.size();i++){
        printf("%d ", vec[i]);
    }
    printf("\n");
}

class Solution {
    int debug;
public:
    Solution(int debug=0):debug(debug){

    }
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, vector<int> >m;

        int first, second;
        for(int i=0;i<numbers.size();i++){
            first = numbers[i];
            m[first];
            m[first].push_back(i);
        }

        for(int i=0;i<numbers.size();i++){
            second = numbers[i];
            first = target - second;
            if(m.find(first) != m.end()){
                vector<int>&vec = m[first];
                if(debug){
                    printf("target=%d second=%d find=%d\n",target,second,first);
                    printfVec(vec);
                }
                if(first == second && vec.size() == 1){
                    continue;
                }
                if(vec.size() == 1){
                    first = i;
                    second = vec[0];
                }else{
                    first = vec[0];
                    second = vec[1];
                }
                break;
            }
        }

        if(first > second){
            int tmp;
            tmp = first;
            first = second;
            second = tmp;
        }

        vector<int> ans;
        ans.push_back(first+1);
        ans.push_back(second+1);

        return ans;
    }
};


void test(){
    srand(time(NULL));
    Solution work(1);

    vector<int> data;
    int target;

    vector<int>ans;

    data.clear();
    printf("test2\n");
    data.push_back(2);
    data.push_back(7);
    data.push_back(11);
    data.push_back(15);
    target = 9;
    printf("\ttest data\n");
    printfVec(data);
    printf("\ttarget : %d\n", target);
    ans = work.twoSum(data, target);
    printf("\ttest ans\n");
    printfVec(ans);
    data.clear();

    data.clear();
    printf("test2\n");
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    target = 6;
    printf("\ttest data\n");
    printfVec(data);
    printf("\ttarget : %d\n", target);
    ans = work.twoSum(data, target);
    printf("\ttest ans\n");
    printfVec(ans);
    data.clear();


    data.clear();
    printf("test3\n");
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(5);
    target = 6;
    printf("\ttest data\n");
    printfVec(data);
    printf("\ttarget : %d\n", target);
    ans = work.twoSum(data, target);
    printf("\ttest ans\n");
    printfVec(ans);
    data.clear();

}

int main(){
    test();
    return 0;
}
