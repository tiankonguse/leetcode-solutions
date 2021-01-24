/*************************************************************************
    > File Name: parsing-a-boolean-expression.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2019年06月30日 11:37:47
    > link:
    > No: 1106. Parsing A Boolean Expression
    > Contest: https://leetcode.com/contest/weekly-contest-143
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    //()
    bool passMore(string& expression, int& start, int flag){
        
        start++; // skip (
        bool ret = passExpr(expression, start);
        while(expression[start] == ','){
            start++; // skip ,
            bool tmp = passExpr(expression, start);
            if(flag){
                ret = ret || tmp;
            }else{
                ret = ret && tmp;
            }
        }
        
        start++; //skip )
        return ret;
    }
	// 1. t 
	// 2. f 
	// 3. !()
	// 4. &()
	// 5. |()
    bool passExpr(string& expression, int& start){
        if(start >= expression.size()){
            return true;
        }
        bool ret = true;
        switch(expression[start]){
            case 't':
                start++; 
                ret = true;
                break;
            case 'f':
                start++; 
                ret = false;
                break;
            case '!':
                start++; 
                ret = !passMore(expression, start, 1);
                break;
            case '|':
                start++; 
                ret = passMore(expression, start, 1);
                break;
            case '&':
                start++; 
                ret = passMore(expression, start, 0);
                break;
        }
        return ret;
    }
    
public:
    bool parseBoolExpr(string expression) {
        int start = 0;
        return passExpr(expression, start);
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
