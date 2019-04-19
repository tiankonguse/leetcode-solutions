/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月19日 16:45:45
 ************************************************************************/


#include "../../include/base.h"
class Solution {
    bool check(int speed, vector<int>& piles, int H) {
        if(speed == 0){
            return false;
        }
        int useTime = 0;
        for(int i=0; i<piles.size(); i++) {
            useTime += (piles[i] + speed - 1)/speed;
            if(useTime > H) {
                return false;
            }
        }
        return true;
    }
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        int maxSpeed = 0;
        for(int i=0; i<piles.size(); i++) {
            maxSpeed = max(maxSpeed, piles[i]);
        }
        int minSpeed = 0, midSpeed;

        while(minSpeed < maxSpeed) {
            midSpeed = (minSpeed + maxSpeed)/2;
            if(check(midSpeed, piles, H)) {
                maxSpeed  = midSpeed;
            } else {
                minSpeed = midSpeed + 1;
            }
        }
        return maxSpeed;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<int> first;
    int second;
    int expectAns;

    first = {3,6,7,11};
    second = 8;
    expectAns = 4;
    TEST_SMP2(Solution, minEatingSpeed, expectAns, first, second);

    first = {30,11,23,4,20};
    second  = 5;
    expectAns = 30;
    TEST_SMP2(Solution, minEatingSpeed, expectAns, first, second);

    first = {30,11,23,4,20};
    second  = 6;
    expectAns = 23;
    TEST_SMP2(Solution, minEatingSpeed, expectAns, first, second);


    first = {5};
    second  = 6;
    expectAns = 1;
    TEST_SMP2(Solution, minEatingSpeed, expectAns, first, second);



    return 0;
}
