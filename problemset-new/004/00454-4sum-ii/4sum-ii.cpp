/*************************************************************************
    > File Name: 4sum-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 23:06:58 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    void add(map<int,int>& s, vector<int>& A, vector<int>& B){
        for(int i=0;i<A.size();i++){
            for(int j=0;j<B.size();j++){
                s[A[i]+B[j]]++;
            }
        }
    }
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        map<int, int> first;
        map<int, int> second;
        add(first, A, B);
        add(second, C, D);
        int ans  = 0;
        for(auto p : first){
            if(second.find(-p.first) != second.end()){
                ans += p.second * second[-p.first];
            }
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int third;
    int four;
    int expectAns;


    first = 1;
    second = 1;
    third = 1;
    four = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
    //TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);
    //TEST_SMP4(Solution, FUNCTION, expectAns, first, second, third, four);
*/
int main() {
    #define CLASS Solution
    #define FUNCTION fourSumCount

    vector<int> first;
    vector<int> second;
    vector<int> third;
    vector<int> four;
    int expectAns;

    first = {1, 2};
    second = {-2,-1};
    third = {-1, 2};
    four = { 0, 2};
    expectAns = 2;
    TEST_SMP4(Solution, FUNCTION, expectAns, first, second, third, four);

    return 0;
}
