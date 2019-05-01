/*
 * Filename: /home/zwk/code/datafirst
 *uctrue/c++/stack/evaluate_reverse_polish_notation/main.cpp
 * Path: /home/zwk/code/datafirst
 *uctrue/c++/stack/evaluate_reverse_polish_notation
 * Created Date: Wednesday, May 1st 2019, 5:38:35 pm
 * Author: zwk
 * 
 * Copyright (c) 2019 Your Company
 */


#include "../../include/base.h"

/// Time Complexity: O(n)
/// Space Complexity: O(n)
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int>sta;
        int ans = 0;

        int first, second, result;
        for(int i=0;i<tokens.size();i++){
            bool operator_flag = ((tokens[i][0] == '+') ||  (tokens[i][0] == '-') ||  (tokens[i][0] == '*') ||  (tokens[i][0] == '/')) && (tokens[i].size() == 1);
            int num = 0;
            if(operator_flag)  {
                if(sta.size() < 2)  {
                    return -999;        // error
                } else if(tokens[i][0] == '+')  {
                    second = sta.top();
                    sta.pop();
                    first = sta.top();
                    sta.pop();
                    result = first + second;
                    sta.push(result);
                } else if(tokens[i][0] == '-')  {
                    second = sta.top();
                    sta.pop();
                    first = sta.top();
                    sta.pop();
                    result = first - second;
                    sta.push(result);
                } else if(tokens[i][0] == '*')  {
                    second = sta.top();
                    sta.pop();
                    first = sta.top();
                    sta.pop();
                    result = first * second;
                    sta.push(result);
                } else if(tokens[i][0] == '/')  {
                    second = sta.top();
                    sta.pop();
                    first = sta.top();
                    sta.pop();
                    result = first / second;
                    sta.push(result);
                }
            } else  {
                num = atoi(tokens[i].c_str());
                sta.push(num);
                result = num;       // consider only one nums in token
            }
        }
        return result;
    }

};


int main() {
    vector<string> first;
    int ans, expectAns;

    //["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9/
    first.clear();
    first.push_back("2");
    first.push_back("1");
    first.push_back("+");
    first.push_back("3");
    first.push_back("*");
    expectAns = 9;
    TEST_SMP1(Solution, evalRPN, expectAns, first);

    //["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
    first.clear();
    first.push_back("4");
    first.push_back("13");
    first.push_back("5");
    first.push_back("/");
    first.push_back("+");
    expectAns = 6;
    TEST_SMP1(Solution, evalRPN, expectAns, first);

    //["-1","1","*","-1","+"] -> ((-1 * 1) + -1) -> -2
    first.clear();
    first.push_back("-1");
    first.push_back("1");
    first.push_back("*");
    first.push_back("-1");
    first.push_back("+");
    expectAns = -2;
    TEST_SMP1(Solution, evalRPN, expectAns, first);

    //["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"] -> ((10 * (6 / ((9 + 3) * -11))) + 17) + 5 -> 22
    first.clear();
    first.push_back("10");
    first.push_back("6");
    first.push_back("9");
    first.push_back("3");
    first.push_back("+");
    first.push_back("-11");
    first.push_back("*");
    first.push_back("/");
    first.push_back("*");
    first.push_back("17");
    first.push_back("+");
    first.push_back("5");
    first.push_back("+");
    expectAns = 22;
    TEST_SMP1(Solution, evalRPN, expectAns, first);

    return 0;
}
