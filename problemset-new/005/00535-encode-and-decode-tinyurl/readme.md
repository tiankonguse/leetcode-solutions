# 535. Encode and Decode TinyURL
# 535. TinyURL 的加密与解密


TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.



Design the encode and decode methods for the TinyURL service. 

There is no restriction on how your encode/decode algorithm should work. 

You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.



TinyURL 是一种 URL 简化服务， 比如：当你输入一个 URL https://leetcode.com/problems/design-tinyurl 时，它将返回一个简化的URL http://tinyurl.com/4e9iAk 。请你设计一个类来加密与解密 TinyURL 。

加密和解密算法如何设计和运作是没有限制的，你只需要保证一个 URL 可以被加密成一个 TinyURL ，并且这个 TinyURL 可以用解密方法恢复成原本的 URL 。

实现 Solution 类：

Solution() 初始化 TinyURL 系统对象。
String encode(String longUrl) 返回 longUrl 对应的 TinyURL 。
String decode(String shortUrl) 返回 shortUrl 原本的 URL 。题目数据保证给定的 shortUrl 是由同一个系统对象加密的。
 

示例：

输入：url = "https://leetcode.com/problems/design-tinyurl"
输出："https://leetcode.com/problems/design-tinyurl"

解释：
Solution obj = new Solution();
string tiny = obj.encode(url); // 返回加密后得到的 TinyURL 。
string ans = obj.decode(tiny); // 返回解密后得到的原本的 URL 。
 

提示：

1 <= url.length <= 104
题目数据保证 url 是一个有效的 URL

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/encode-and-decode-tinyurl
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。




