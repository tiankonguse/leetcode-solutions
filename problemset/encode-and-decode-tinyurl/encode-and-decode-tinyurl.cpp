/*************************************************************************
  > File Name: encode-and-decode-tinyurl.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2017年07月11日
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
class Solution {
public:
    std::vector<std::string> m_list;
    std::map<std::string, std::string> m_hash;
    // Encodes a URL to a shortened URL.ss
    std::string encode(const std::string& longUrl) {
        if(longUrl.size()%2){
            return encodeInc(longUrl);
        }else{
            return encodeHash(longUrl);
        }
    }
    
    std::string encodeInc(const std::string& longUrl) {
        char buf[128];
        snprintf(buf, sizeof(buf), "%d", (int)m_list.size());
        m_list.push_back(longUrl);
        return buf;
    }
    
    std::string encodeHash(const std::string& longUrl) {
        if(m_hash.find(longUrl) != m_hash.end()){
            return m_hash[longUrl];
        }else{
            char buf[128];
            snprintf(buf, sizeof(buf), "%d", (int)m_list.size());
            m_hash[longUrl] = buf;
            m_list.push_back(longUrl);
            return m_hash[longUrl];
        }
    }

    // Decodes a shortened URL to its original URL.
    std::string decode(const std::string& shortUrl) {
        return m_list[atoi(shortUrl.c_str())];
    }
};

void test(std::string url){
    Solution solution;
    std::string newUrl = solution.decode(solution.encode(url));
    printf("%s\n", url.c_str());
    printf("test %s\n", newUrl == url?"YES":"NO");
    
}

int main() {
    test("https://leetcode.com/problems/design-tinyurl");

    return 0;
}
