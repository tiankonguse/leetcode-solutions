// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
public:
    int passThePillow(int n, int time) {
        int a = time / (n-1);
        int b = time % (n-1);
        if(a % 2 == 0){
          return b + 1;
        }else{
          return n - b;
        }
    }
};