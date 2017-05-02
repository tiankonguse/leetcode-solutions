	/**********	***************************************************************
  > File Name: permutation-in-string.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
***********************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        return true;
    }
};




int main() {
	Solution work;
	bool ans;
	string s1;
	string s2;
	char buffer1[2000] = "123";
	char buffer2[2000] = "123";
	
	while(~scanf("%s%s", buffer1, buffer2)){
		s1 = buffer1;
		s2 = buffer2;
		ans = work.checkInclusion(s1, s2);
		printf("Input: \n s1=\"%s\"\n s2=\"%s\" \nOutput: \"%d\"\n", s1.c_str(), s2.c_str(), ans);
	}

    return 0;
}
