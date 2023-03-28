// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
public:
    vector<int> evenOddBit(int n) {
        int odd = 0, even = 0;
        int flag = 0;
        while(n){
          if(flag == 0){
            even += n%2;
          }else{
            odd += n%2;
          }
          n /= 2;
          flag = 1 - flag;
        }
        return {even, odd};
    }
};