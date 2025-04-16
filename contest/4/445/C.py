from collections import Counter
from functools import lru_cache
import math

MAX = 10005
factorial = [1] * MAX
for i in range(1, MAX):
    factorial[i] = factorial[i - 1] * i

def count_permutations(freq_tuple):
    total = sum(freq_tuple)
    res = factorial[total]
    for f in freq_tuple:
        res //= factorial[f]
    return res

def kth_smallest_permutation(n, counter, k):
    print(counter)
    current_len = n
    chars = sorted(counter.keys())
    freq_tuple = tuple(counter[c] for c in chars)
    total_possible = count_permutations(freq_tuple)
    if k > total_possible:
        return ""  # 所有合法排列数不足 k 个

    result = []
    for _ in range(n):
        for ch in chars:
            if counter[ch] == 0:
                continue
            
            total_possible_with_char = total_possible * counter[ch] // current_len
            if k <= total_possible_with_char: # 选择
                counter[ch] -= 1
                current_len -= 1
                total_possible = total_possible_with_char
                result.append(ch)
                break
            else:
                k -= total_possible_with_char # 不选择

    return ''.join(result)

class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        n = len(s)
        if n == 1:
            if k == 1:
                return s
            else:
                return ""
        counter = Counter(s)
        
        # 找到出现次数为奇数的字符
        odd_char = ''
        for ch, count in counter.items():
            if count % 2 == 1:
                odd_char = ch
                counter[ch] -= 1
            counter[ch] //= 2
        
        # 构造第 k 小的回文串
        kth_half = kth_smallest_permutation(n//2, counter, k)
        if kth_half == "":
            return ""
        return kth_half + odd_char + kth_half[::-1]