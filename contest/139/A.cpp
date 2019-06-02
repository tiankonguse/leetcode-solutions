/*************************************************************************
    > File Name: greatest-common-divisor-of-strings.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  2 10:24:26 2019
    > link: https://leetcode.com/problems/greatest-common-divisor-of-strings/
    > No: 1071. Greatest Common Divisor of Strings
    > Contest: https://leetcode.com/contest/weekly-contest-139
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    int gcd(int a, int b) {
        if(b == 0) return a;
        else return gcd(b, a % b);
    }
   bool check(string& str1, string& str2, int len){
       if(len == 0){
           return true;
       }
       if(str1.size() % len != 0 || str2.size() % len != 0){
           return false;
       }
       string base=str1.substr(0, len);

       for(int i=0,j=0;i<str1.size();i++,j++){
           if(j == len){
               j = 0;
           }
           if(str1[i] != str1[j]){
               return false;
           }
       }
       for(int i=0,j=0;i<str2.size();i++,j++){
           if(j == len){
               j = 0;
           }
           if(str2[i] != str1[j]){
               return false;
           }
       }

       return true;
   }


public:
    string gcdOfStrings(string str1, string str2) {
        if(str1.size() < str2.size()){
            swap(str1, str2);
        }
        int maxLen = gcd(str1.size(), str2.size());

        if(strncmp(str1.c_str(), str2.c_str(), str2.size()) != 0){
            return "";
        }

        for(int i=maxLen; i>0;i--){
            if(check(str1, str2, i)){
                return str1.substr(0,i);
            }
        }
        return "";
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
