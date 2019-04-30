/*************************************************************************
  > File Name: divide-two-integers.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2016年06月04日 星期六 17时43分10秒
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
using namespace std;

#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif


const LL MIN_INT = -2147483648;
const LL MAX_INT = 2147483647;;
const LL NEGATIVE = -1;
const LL ZERO = 0;
const LL TWO = 2;
const LL ONE = 1;

class Solution {


    int debug;

    LL getSign(LL& left, LL& right){
        LL sign = ZERO;
        if(left < ZERO){
            sign++;
            left = -left;
        }
        if(right < ZERO){
            sign++;
            right = -right;
        }
        if(sign == ZERO || sign == TWO){
            sign = ONE;
        }else{
            sign = NEGATIVE;
        }
        return sign;
    }

    
    LL getLev(LL& left, LL right){
        LL lev = 1;
        while(left >= right){
            right <<= 1;
            lev <<= 1;
        }
        right >>= 1;
        lev >>= 1;
        left -= right;
        return lev;
    }

    LL cal(LL left, LL right){
        if(left < right){
            return 0;
        } 
        LL lev  = getLev(left, right);
        return lev + cal(left, right);
    }
public:

    Solution(int debug = 0):debug(debug){}
    void openDebug(){
        debug = 1;
    }

    int divide(int dividend, int divisor) {
        LL left = dividend;
        LL right = divisor;

        if(right == ZERO){
            return MAX_INT;
        }

        if(left == MIN_INT and right == NEGATIVE){
            return MAX_INT;
        }

        if(left == ZERO){
            return ZERO;
        }

        LL sign = getSign(left, right);    
        LL ret = cal(left, right);
        if(this->debug)printf("sign=%lld left=%lld right=%lld ret=%lld\n", sign, left, right, ret);
        if(sign == NEGATIVE){
            ret = -ret;
        }
        return ret;
    }

};


int main(int argc, char**argv) {
    if(argc != 3){
        return 1;
    }
    LL left = atoi(argv[1]);
    LL  right= atoi(argv[2]);
    Solution work;
    work.openDebug();
    printf("%lld/%lld = %lld(div) %lld(class)\n", left, right, left/right, work.divide(left, right));


    return 0;
}

