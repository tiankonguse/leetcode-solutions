class Solution {
   public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        string s = to_string(x);
        std::reverse(s.begin(), s.end());
        long long a = std::stoll(s);
        if (a - x == 0) {
            return true;
        } else {
            return false;
        }
    }
};
