/*************************************************************************
    > File Name: add-binary.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > link: https://leetcode.com/problems/add-binary/
 ************************************************************************/

#include "base.h"


class BigNumber {
public:
    int val;
    BigNumber(int val = 0):val(val) {
    }
    BigNumber operator-(const BigNumber &second)const {
        return BigNumber(this->val - second.val);
    }
    BigNumber operator*(const BigNumber &second)const {
        return BigNumber(this->val * second.val);
    }
    bool operator<(const BigNumber &second)const {
        return this->val < second.val;
    }


};

BigNumber operator+(const BigNumber &first, const BigNumber &second) {
    return BigNumber(first.val + second.val);
}


bool operator!(const BigNumber &first) {
    return !first.val;
}


BigNumber operator++(BigNumber &first, int) {
    BigNumber tmp = first;
    first.val++;
    return tmp;
}
BigNumber& operator++(BigNumber &first) {
    first.val++;
    return first;
}



int main() {
    BigNumber first(8);
    BigNumber second(12);
    printf("first=%d second=%d\n", first.val, second.val);

    BigNumber third = (second - first)* (second + first);
    printf("%d\n", third.val);


    printf("first < second = %d\n", first<second);

    BigNumber afterplus = first++;
    BigNumber beforplus = ++second;

    printf("after=%d befor=%d\n", afterplus.val,beforplus.val );

    printf("!first=%d\n", !first);

    return 0;
}
