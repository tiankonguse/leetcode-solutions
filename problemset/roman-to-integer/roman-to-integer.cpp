/*************************************************************************
    > File Name: roman-to-integer.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月17日 星期五 01时34分52秒
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
    struct RN{
        int c;
        int ans;
    };
    int getVal(char c){
        int ans = 0;
        switch(c){
            case 'I':
            case 'i':
                ans = 1;
                break;
            case 'V':
            case 'v':
                ans = 5;
                break;
            case 'X':
            case 'x':
                ans = 10;
                break;
            case 'L':
            case 'l':
                ans = 50;
                break;
            case 'C':
            case 'c':
                ans = 100;
                break;
            case 'D':
            case 'd':
                ans = 500;
                break;
            case 'M':
            case 'm':
                ans = 1000;
                break;
            default:
                ans = 0;
        }
        return ans;
    }
    stack<RN> sta;
public:
    int romanToInt(string s) {
        while(!sta.empty()){
            sta.pop();
        }

        int size = s.length();
        RN now;
        for(int i=0;i<size;i++){
            now.c = getVal(s[i]);
            now.ans = now.c;

            while(!sta.empty()){
                if(sta.top().c < now.c){
                    now.ans -= sta.top().ans;
                    sta.pop();
                }else{
                    break;
                }
            }
            sta.push(now);
        }

        int ans = 0;
        while(!sta.empty()){
            ans += sta.top().ans;
            sta.pop();
        }

        return ans;
    }
};


struct Data{
    const char* s;
    int ans;
    Data(const char* s, int ans=0):s(s),ans(ans){

    }

};

void test(){
    srand(time(NULL));
    Solution work;

    Data data[] = {
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"X", 10},
        {"L", 50},
        {"XLI", 41},
        {"IXL", 41},
        {"XIV", 14},
        {"XIX", 19},
        {"C", 100},
        {"D", 500},
        {"XLIV", 44},
        {"DCCCXC", 890},
        {"M", 1000},
        {"MD", 1500},
        {"I",1},
        {"XXXII",32},
        {"LXIII",63},
        {"XCIV",94},
        {"II",2},
        {"XXXIII",33},
        {"LXIV",64},
        {"XCV",95},
        {"III",3},
        {"XXXIV",34},
        {"LXV",65},
        {"XCVI",96},
        {"IV",4},
        {"XXXV",35},
        {"LXVI",66},
        {"XCVII",97},
        {"V",5},
        {"XXXVI",36},
        {"LXVII",67},
        {"XCVIII",98},
        {"VI",6},
        {"XXXVII",37},
        {"LXVIII",68},
        {"XCIX",99},
        {"VII",7},
        {"XXXVIII",38},
        {"LXIX",69},
        {"C",100},
        {"VIII",8},
        {"XXXIX",39},
        {"LXX",70},
        {"IX",9},
        {"XL",40},
        {"LXXI",71},
        {"X",10},
        {"XLI",41},
        {"LXXII",72},
        {"DI",501},
        {"XI",11},
        {"XLII",42},
        {"LXXIII",73},
        {"DL",550},
        {"XII",12},
        {"XLIII",43},
        {"LXXIV",74},
        {"DXXX",530},
        {"XIII",13},
        {"XLIV",44},
        {"LXXV",75},
        {"DCCVII",707},
        {"XIV",14},
        {"XLV",45},
        {"LXXVI",76},
        {"DCCCXC",890},
        {"XV",15},
        {"XLVI",46},
        {"LXXVII",77},
        {"MD",1500},
        {"XVI",16},
        {"XLVII",47},
        {"LXXVIII",78},
        {"MDCCC",1800},
        {"XVII",17},
        {"XLVIII",48},
        {"LXXIX",79},
        {"CM",900},
        {"XVIII",18},
        {"XLIX",49},
        {"LXXX",80},
        {"XIX",19},
        {"L",50},
        {"LXXXI",81},
        {"XX",20},
        {"LI",51},
        {"LXXXII",82},
        {"XXI",21},
        {"LII",52},
        {"LXXXIII",83},
        {"XXII",22},
        {"LIII",53},
        {"LXXXIV",84},
        {"XXIII",23},
        {"LIV",54},
        {"LXXXV",85},
        {"XXIV",24},
        {"LV",55},
        {"LXXXVI",86},
        {"XXV",25},
        {"LVI",56},
        {"LXXXVII",87},
        {"XXVI",26},
        {"LVII",57},
        {"LXXXVIII",88},
        {"XXVII",27},
        {"LVIII",58},
        {"LXXXIX",89},
        {"XXVIII",28},
        {"LIX",59},
        {"XC",90},
        {"XXIX",29},
        {"LX",60},
        {"XCI",91},
        {"XXX",30},
        {"LXI",61},
        {"XCII",92},
        {"XXXI",31},
        {"LXII",62},
        {"XCIII",93},
    };
    string s;
    int ans;

    int len = sizeof(data)/sizeof(Data);

    for(int i=0;i<len;i++){
        s = data[i].s;
        ans = work.romanToInt(s);
        printf("s=%s ans=%d expect=%d %s\n",s.c_str(), ans, data[i].ans, data[i].ans==ans?"YES":"NO");
    }
}

int main(){
    test();
    return 0;
}
