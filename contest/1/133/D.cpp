/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 10:12:57 2019
    > Contest:
    > Title:
    > Link:
 ************************************************************************/

#include "../../include/base.h"

class StreamChecker {
    vector<string> words;
    string queStr;
public:
    StreamChecker(vector<string>& wordsParam) {
        for(int i=0; i<wordsParam.size(); i++) {
            reverse(wordsParam[i].begin(), wordsParam[i].end());
            words.push_back(wordsParam[i]);
        }
        sort(words.begin(), words.end());
    }

    int findMin(int index, char letter, int minPos, int maxPos) {
        int midPos;
        while(minPos < maxPos) {
           //printf("findMin min=%d max=%d\n", minPos, maxPos);
            midPos = (minPos + maxPos)/2;
            if(words[midPos][index] < letter) {
                minPos = midPos + 1;
            } else {
                maxPos = midPos;
            }
        }

        if(minPos == words.size()){
            return -1;
        }
        if(words[minPos][index] == letter) {
            return minPos;
        } else {
            return -1;
        }
    }
    int findMax(int index, char letter, int minPos, int maxPos) {
        int midPos;
        while(minPos < maxPos) {
           //printf("findMax min=%d[%s] max=%d[%s]\n", minPos, words[minPos].c_str(), maxPos, words[minPos].c_str());
            midPos = (minPos + maxPos)/2;
            if(words[midPos][index] <= letter) {
                minPos = midPos + 1;
            } else {
                maxPos = midPos;
            }
        }
        if(words[maxPos-1][index] == letter) {
            return maxPos;
        } else {
            return -1;
        }
    }

    bool query(char letter) {
        queStr.push_back(letter);
        //printf("query [%s]\n", queStr.c_str());

        int minPos = 0;
        int maxPos = words.size();
        int index = 0;

        bool ans = false;
        for(int i=queStr.size()-1; i>=0; i--) {
            minPos = findMin(index, queStr[i], minPos, maxPos);
            if(minPos == -1) {
                ans = false;
                break;
            }
            maxPos = findMax(index, queStr[i], minPos, maxPos);
            if(maxPos == -1) {
                ans = false;
                break;
            }
            //printf("query min=%d max=%d\n", minPos, maxPos);
            index++;
            if(words[minPos].length() == index) {
                ans = true;
                break;
            }
            if(index > words[minPos].length()) {
                ans = false;
                break;
            }
        }
        //printf("query ans[%d]\n", ans);
        return ans;
    }
};

template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    //StreamChecker work;
    StreamChecker work(initData); //°´ÐèÐÞ¸Ä

    for(int i=0; i<opreateParam.size(); i++) {
        bool ansTmp = true;
        if(opreateParam[i] == "query") {
            ansTmp = work.query(firstData[i]);
        }
        ans.push_back(ansTmp);
    }
    int index = getIndex();
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("opreateParam", opreateParam);
        output(" initData", initData);
        output("firstData", firstData);
        output("      ans", ans);
        output("expectAns", expectAns);

    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");
}

int main() {
    vector<string> opreateParam;
    vector<string> initData;
    vector<char> firstData;
    vector<bool> expectAns;

    opreateParam= {"query","query","query","query","query","query","query","query","query","query","query","query"};
    initData = {"cd","f","kl"};
    firstData = {{'a'},{'b'},{'c'},{'d'},{'e'},{'f'},{'g'},{'h'},{'i'},{'j'},{'k'},{'l'}};
    expectAns = {false,false,false,true,false,true,false,false,false,false,false,true};
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}
