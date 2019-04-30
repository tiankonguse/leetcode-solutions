/*************************************************************************
    > File Name: compare-version-numbers.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月16日 星期四 23时00分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;

class Solution {
    struct Version{
        int pos;
        string left;
        int len;
        Version(string str=""){
            left = str;
            pos = 0;
            len = left.length();
        }
        int getNext(){
            size_t found = left.find(".", pos);
            if(found == string::npos){
                if(len > pos){
                    found = len;
                }else{
                    return 0;
                }
            }
            int val = atoi(left.c_str() + pos);
            pos = found + 1;
            return val;
        }
        int empty(){
            return len <= pos;
        }

    };
public:
    int compareVersion(string version1, string version2) {
        Version first(version1);
        Version second(version2);

        int one, two;

        while(1){
            if(first.empty() && second.empty()){
                return 0;
            }
            one = first.getNext();
            two = second.getNext();
            printf("%d ? %d\n", one, two);

            if(one > two){
                return 1;
            }else if(one < two){
                return -1;
            }

        }

        return 0;
    }
};


void test(){
    srand(time(NULL));
    Solution work;

    string one;
    string two;
    int ans;

    one="1";
    two="2";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);


    one="1.1";
    two="2";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);


    one="1";
    two="2.1";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

    one="2.1";
    two="2.1";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

    one="2.12";
    two="2.1";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

    one="2.12";
    two="2.2";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

    one="2.12";
    two="2.12.0";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

    one="2.12.0.1";
    two="2.12.0";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

    one="2.12.0.0";
    two="2.12.0.0.0.0";
    ans = work.compareVersion(one, two);
    printf("one = %s\ntwo=%s\nans=%d\n\n", one.c_str(), two.c_str(), ans);

}

int main(){
    test();
    return 0;
}
