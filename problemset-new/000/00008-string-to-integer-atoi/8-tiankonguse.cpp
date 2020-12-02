/*************************************************************************
    > File Name: string-to-integer-atoi.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月17日 星期五 00时58分49秒
 ************************************************************************/

#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
    long long min;
    long long max;
public:
    Solution(){
        min = 2147483648;
        max = 2147483647;
    }
    bool isdigit(char c){
        if(c>='0' && c <= '9'){
            return true;
        }else{
            return false;
        }
    }
    bool isspace(char c){
        switch(c){
            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\f':
            case '\r':
                return true;
            default:
                return false;
        }
    }
    int myAtoi(const string& str) {
        long long ans = 0;
        int size = str.length();
        int pos = 0;
        int sign = 1;

        for(; pos < size; pos++){
            if(!isspace(str[pos])){
                break;
            }
        }

        if(pos == size){
            return 0;
        }
    
        if(str[pos] == '+'){
            sign = 1;
            pos = pos + 1;
        }else if(str[pos] == '-'){
            sign = -1;
            pos = pos + 1;
        }

        for(; pos < size; pos++){
            if(isdigit(str[pos])){
                ans = ans * 10 + (str[pos] - '0');
                if(ans * sign <= -min){
                    ans = min;
                    break;
                }else if(ans * sign >= max){
                    ans = max;
                    break;
                }
            }else{
                break;
            }
        }
        return ans*sign;
    }
};


int main(){
  TEST_SMP1(Solution, myAtoi, INT_MIN , std::string(" -9223372036854775809"));
  TEST_SMP1(Solution, myAtoi, INT_MIN, std::string(" -9223372036854775808"));
  TEST_SMP1(Solution, myAtoi, INT_MIN, std::string(" -3147483648"));
  TEST_SMP1(Solution, myAtoi, INT_MIN, std::string(" -2147483648"));
  TEST_SMP1(Solution, myAtoi, -7, std::string(" -07"));
  TEST_SMP1(Solution, myAtoi, 2147483647, std::string(" 9223372036854775819"));
  TEST_SMP1(Solution, myAtoi, 2147483647, std::string(" 9223372036854775809"));
  TEST_SMP1(Solution, myAtoi, 2147483647, std::string(" 9223372036854775808"));
  TEST_SMP1(Solution, myAtoi, 2147483647, std::string(" 9223372036854775807"));
  TEST_SMP1(Solution, myAtoi, 2147483, std::string(" 2147483sdad648"));
  TEST_SMP1(Solution, myAtoi, 2147483647, std::string(" 2147483648"));
  TEST_SMP1(Solution, myAtoi, 2147483647, std::string(" 2147483647"));
  TEST_SMP1(Solution, myAtoi, 0, std::string(" + -"));
  TEST_SMP1(Solution, myAtoi, 0, std::string(" + 7"));
  TEST_SMP1(Solution, myAtoi, 7, std::string(" +7"));
  TEST_SMP1(Solution, myAtoi, 9, std::string(" 09"));
  TEST_SMP1(Solution, myAtoi, 1, std::string(" 01"));
  TEST_SMP1(Solution, myAtoi, 1, std::string("1"));
  TEST_SMP1(Solution, myAtoi, 0, std::string(""));
    return 0;
}
