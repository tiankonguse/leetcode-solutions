#include <bits/stdc++.h>

#include "base.h"
using namespace std;


typedef long long ll;
class Solution {
public:
    int appendCharacters(const string& s, const string& t) {
        int ans = 0;
        int si = 0, sn = s.size();
        for(auto c: t){
            while(si < sn && s[si] != c){
              si++;
            }
          if(si == sn){
            ans++;
          }else{
              si++;
          }
        }
        return ans;
    }
};