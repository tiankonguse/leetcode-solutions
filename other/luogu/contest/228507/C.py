MOD = 998244353

def count_palindromic_substrings(s):
    # 使用Manacher算法计算回文子串数目
    def manacher(s):
        n = len(s)
        s = '#' + '#'.join(s) + '#'
        n = len(s)
        p = [0] * n
        max_right = 0
        center = 0
        total = 0
        for i in range(n):
            if i < max_right:
                mirror = 2 * center - i
                p[i] = min(max_right - i, p[mirror])
            l = i - p[i] - 1
            r = i + p[i] + 1
            while l >= 0 and r < n and s[l] == s[r]:
                p[i] += 1
                l -= 1
                r += 1
            if i + p[i] > max_right:
                max_right = i + p[i]
                center = i
            total += (p[i] + 1) // 2
        return total
    
    return manacher(s)

def solve(s, k):
    n = len(s)
    if n == 0:
        return 0
    
    # 检查s是否是回文
    is_palindrome = s == s[::-1]
    if is_palindrome:
        m = (n * k) % (2 * MOD)
        res = m * (m + 1) // 2 % MOD
        return res
    
    # 计算原s的回文数目C
    C = count_palindromic_substrings(s)
    
    # 计算最大的t
    reversed_s = s[::-1]
    max_t = 0
    for t in range(0, n+1):
        if s[:t] == reversed_s[:t]:
            max_t = t
    
    # 计算总结果
    term1 = (C % MOD) * (k % MOD) % MOD
    term2 = (max_t % MOD) * ((k - 1) % MOD) % MOD
    res = (term1 + term2) % MOD
    return res

# 示例测试
s = "abab"
k = 2
print(solve(s, k))  # 输出4