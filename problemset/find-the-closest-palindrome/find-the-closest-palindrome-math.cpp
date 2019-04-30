	/**********	***************************************************************
  > File Name: find-the-closest-palindrome.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
***********************************************************************/

#include "../../include/base.h"

class Solution {
	//10幂数不是回文串。10^幂+1和10^幂-1肯定都是回文串
	bool isTenPower(char* inputBuffer, int inputLength){
		if(inputBuffer[0] != '1'){
			return false;
		}
		for(int i = 1; i < inputLength; i++){
			if(inputBuffer[i] != '0'){
				return false;
			}
		}
		return true;
	}
	
	void reversalCover(char* input, int highBegin, int inputLength){
		for(int tailPos = inputLength  -1, headPos = 0; tailPos > headPos; tailPos--,headPos++){
			input[tailPos] = input[headPos];
		}
		
	}
	
	//由于求最大值和最小值合并位通用逻辑了，所以理解难度大点，大家可以使用其中一个模拟一下
	long long getNearestAnsMath(const long long inputNum, const int sign, const char baseChar){
		char inputBuffer[20];
		const int inputLength = snprintf(inputBuffer, sizeof(inputBuffer), "%lld", inputNum);
		
		//个位数自身就是回文串
		if(inputNum <= 9){
			return inputNum; 
		}	
		
		//对10幂数特殊判断，10^幂+1和10^幂-1肯定都是回文串
		if(isTenPower(inputBuffer, inputLength)){
			//小答案刚好对于减一， 大答案刚好加1
			return inputNum + sign;
		}
		
		//第一步求出高位
		int highBegin = 0;
		int highEnd = (inputLength+1)/2;//需要小于，不
		
		char ansBuffer[20];
		memcpy(ansBuffer, inputBuffer, inputLength + 1);//填充高部
		reversalCover(ansBuffer, highBegin, inputLength);//翻转覆盖
	
		//检查是否满足情况
		if(strncmp(ansBuffer, inputBuffer, inputLength) * sign >= 0){
			return atoll(ansBuffer);
		}
		
		//否则加减一则为最优值
		ansBuffer[highEnd] = '\0';
		long long highNum = atoll(ansBuffer) + sign;
		snprintf(ansBuffer, sizeof(ansBuffer), "%lld", highNum);
		reversalCover(ansBuffer, highBegin, inputLength);//翻转覆盖

		return atoll(ansBuffer);
	}
	
	//得到小于等于inputNum的最大的回文串
	long long getNearestSmallAns(const long long inputNum){
		return getNearestAnsMath(inputNum, -1, '0');
	}
	//得到大于等于inputNum的最小的回文串
	long long getNearestBigAns(const long long inputNum){
		return getNearestAnsMath(inputNum, 1, '9');
	}
public:
    std::string nearestPalindromic(const std::string& n) {
		long long inputNum = atoll(n.c_str());
		//printf("inputnum = %lld\n", inputNum);
        long long smallAns = getNearestSmallAns(inputNum - 1);
		long long bigAns = getNearestBigAns(inputNum + 1);
		
		
		//printf("smallAns = %lld\n", smallAns);
		//printf("bigAns = %lld\n", bigAns);
		long long smallAnsDis = inputNum - smallAns;
		long long bigAnsDis = bigAns - inputNum;
		
		long long ans = 0;
		if(smallAnsDis <= bigAnsDis){
			ans = smallAns;
		}else{
			ans = bigAns;
		}
		
		char buffer[20];
		snprintf(buffer, sizeof(buffer), "%lld", ans);
		return buffer;
    }
};




int main() {
	Solution work;
	string ans;
	string input;
	char buffer[20] = "123";
	
	while(~scanf("%s", buffer)){
		input = buffer;
		ans = work.nearestPalindromic(input);
		printf("Input: %s Output: %s\n", input.c_str(), ans.c_str());
	}

    return 0;
}
