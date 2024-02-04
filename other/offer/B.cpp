#include <iostream>
#include "bits/stdc++.h"
using namespace std;

bool cmp(string a, string b)
{
    return a < b;
}

void SortWords(string &s)
{
    vector<string> strVec;
    string tmp = "";
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') {
            strVec.push_back(tmp);
            tmp  = ""; 
        } else {
            tmp += s[i];
        }
    }
    if (tmp.size() > 0) {
        strVec.push_back(tmp);
    }
    cout << s.size();
    sort(strVec.begin(), strVec.end(), cmp);
    
    for (string s : strVec) {
        cout << s << " ";
    }
}

int main() {
    //int a;
    //cin >> a;
    // cout << "Hello World!" << endl;
    string str;
    cin >> str;
    SortWords(str);
}