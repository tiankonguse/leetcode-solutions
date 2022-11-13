#include <bits/stdc++.h>

#include "base.h"
using namespace std;


class Solution {
public:
    string customSortString(const string& order, string s) {
        vector<int> scores(26, -1);
        for(int i=0;i <= order.length();i++){
            scores[order[i] - 'a'] = i;
        }
        sort(s.begin(), s.end(), [&scores](char a, char b){
            return scores[a-'a'] < scores[b - 'a'];
        });
        return s;
    }
};

