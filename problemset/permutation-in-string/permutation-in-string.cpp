	/**********	***************************************************************
  > File Name: permutation-in-string.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
***********************************************************************/

#include "../../include/base.h"

class Solution {
	struct StatStr{
		int num[256];
		int diff;
		StatStr(){
			diff = 0;
			memset(num, 0, sizeof(num));
		}
		void add(int pos){
			if(num[pos] == 0){
				diff++;
			}
			num[pos]++;
			if(num[pos] == 0){
				diff--;
			}
		}
		void minute(int pos){
			if(num[pos] == 0){
				diff++;
			}
			num[pos]--;
			if(num[pos] == 0){
				diff--;
			}
		}
	};
public:
    bool checkInclusion(string s1, string s2) {
		StatStr baseStat;
		if(s2.length() < s1.length()){
			return false;
		}
		for(int i=0;i < s1.length(); i++){
			baseStat.add(s1[i]);
		}
		
		for(int i = 0; i< s1.length() ; i++){
			baseStat.minute(s2[i]);
		}
		if(baseStat.diff == 0){
			return true;
		}
		for(int i = 0, j = s1.length(); j < s2.length(); j++,i++){
			baseStat.add(s2[i]);
			baseStat.minute(s2[j]);
			if(baseStat.diff == 0){
				return true;
			}
		}
		
		
        return false;
    }
};

void test(string s1, string s2){
	Solution work;
	bool ans;
	ans = work.checkInclusion(s1, s2);
	printf("Input: \n s1=\"%s\"\n s2=\"%s\" \nOutput: \"%d\"\n", s1.c_str(), s2.c_str(), ans);
}


int main() {
	char buffer1[2000] = "123";
	char buffer2[2000] = "123";
	
	test("ab", "eidbaooo");
	test("ab", "eidboaoo");
	
	
	while(~scanf("%s%s", buffer1, buffer2)){
		test(buffer1, buffer2);
	}

    return 0;
}
