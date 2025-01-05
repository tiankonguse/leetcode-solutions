from sys import stdin
import math
 
class FastIO:
    def __init__(self):
        self.random_seed = 0
        self.flush = False
        self.inf = 1 << 32
        self.dire4 = [(0, -1), (0, 1), (1, 0), (-1, 0)]
        self.dire8 = [(0, -1), (0, 1), (1, 0), (-1, 0)] + [(1, -1), (1, 1), (-1, -1), (-1, 1)]
        return
 
    @staticmethod
    def read_int():
        return int(stdin.readline().rstrip())
 
    @staticmethod
    def read_float():
        return float(stdin.readline().rstrip())
 
    @staticmethod
    def read_list_ints():
        return list(map(int, stdin.readline().rstrip().split()))
 
    @staticmethod
    def read_list_ints_minus_one():
        return list(map(lambda x: int(x) - 1, stdin.readline().rstrip().split()))
 
    @staticmethod
    def read_str():
        return stdin.readline().rstrip()
 
    @staticmethod
    def read_list_strs():
        return stdin.readline().rstrip().split()
 
    def get_random_seed(self):
        import random
        self.random_seed = random.randint(0, 10 ** 9 + 7)
        return
 
    def st(self, x):
        return print(x, flush=self.flush)
 
    def yes(self, s=None):
        self.st("Yes" if not s else s)
        return
 
    def no(self, s=None):
        self.st("No" if not s else s)
        return
 
    def lst(self, x):
        return print(*x, flush=self.flush)
 
    def flatten(self, lst):
        self.st("\n".join(str(x) for x in lst))
        return
 
    @staticmethod
    def max(a, b):
        return a if a > b else b
 
    @staticmethod
    def min(a, b):
        return a if a < b else b
 
    @staticmethod
    def ceil(a, b):
        return a // b + int(a % b != 0)
 
    @staticmethod
    def accumulate(nums):
        n = len(nums)
        pre = [0] * (n + 1)
        for i in range(n):
            pre[i + 1] = pre[i] + nums[i]
        return pre
 
 

class RangeSetPreSumMaxDynamicDct:
    def __init__(self, n, m=3 * 10 ** 6, initial=-math.inf):
        # dynamic adding point segment tree in which n can be 1e9
        self.n = n
        self.initial = initial
        self.pre_sum_max = [0] * m
        self.sum = [0] * m
        self.lazy_tag = [0] * m  # lazy tag must be initial math.inf
        self.dct = dict()
        self.ind = 1
        return

    def _produce(self, i):
        if i not in self.dct:
            self.dct[i] = self.ind
            self.ind += 1
        while self.ind >= len(self.pre_sum_max):
            self.pre_sum_max.append(0)
            self.sum.append(0)
            self.lazy_tag.append(self.initial)
        return

    def _push_down(self, i, s, m, t):
        self._produce(i)
        if self.lazy_tag[self.dct[i]] != self.initial:
            self._make_tag(i << 1, s, m, self.lazy_tag[self.dct[i]])
            self._make_tag((i << 1) | 1, m + 1, t, self.lazy_tag[self.dct[i]])
            self.lazy_tag[self.dct[i]] = self.initial

    def _push_up(self, i):
        self._produce(i)
        self._produce(i << 1)
        self._produce((i << 1) | 1)
        self.sum[self.dct[i]] = self.sum[self.dct[i << 1]] + self.sum[self.dct[(i << 1) | 1]]
        self.pre_sum_max[self.dct[i]] = max(self.pre_sum_max[self.dct[i << 1]],
                                            self.sum[self.dct[i << 1]] + max(0, self.pre_sum_max[
                                                self.dct[(i << 1) | 1]]))
        return

    def _make_tag(self, i, s, t, val):
        self._produce(i)
        self.pre_sum_max[self.dct[i]] = val * (t - s + 1) if val >= 0 else val
        self.sum[self.dct[i]] = val * (t - s + 1)
        self.lazy_tag[self.dct[i]] = val
        return

    def range_set(self, left, right, val):
        stack = [(0, self.n - 1, 1)]
        while stack:
            s, t, i = stack.pop()
            if i >= 0:
                if left <= s and t <= right:
                    self._make_tag(i, s, t, val)
                    continue

                m = s + (t - s) // 2
                self._push_down(i, s, m, t)
                stack.append((s, t, ~i))

                if left <= m:
                    stack.append((s, m, i << 1))
                if right > m:
                    stack.append((m + 1, t, (i << 1) | 1))
            else:
                i = ~i
                self._push_up(i)
        return

    def range_sum(self, left, right):
        if left > right:
            return 0
        stack = [(0, self.n - 1, 1)]
        ans = 0
        while stack:
            s, t, i = stack.pop()
            if left <= s and t <= right:
                ans += self.sum[self.dct[i]]
                continue
            m = s + (t - s) // 2
            self._push_down(i, s, m, t)
            if left <= m:
                stack.append((s, m, i << 1))
            if right > m:
                stack.append((m + 1, t, (i << 1) | 1))
        return ans

    def range_pre_sum_max(self, left):
        stack = [(0, self.n - 1, 1)]
        ans = self.initial
        pre_sum = 0
        while stack:
            s, t, i = stack.pop()
            self._produce(i)
            if t <= left:
                ans = max(ans, pre_sum + self.pre_sum_max[self.dct[i]])
                pre_sum += self.sum[self.dct[i]]
                continue
            m = s + (t - s) // 2
            self._push_down(i, s, m, t)
            if left > m:
                stack.append((m + 1, t, (i << 1) | 1))
            stack.append((s, m, i << 1))
        return ans

    def range_pre_sum_max_bisect_left(self, val):
        s, t, i = 0, self.n - 1, 1
        pre_sum = 0
        while s < t:
            m = s + (t - s) // 2
            self._push_down(i, s, m, t)
            if pre_sum + self.pre_sum_max[self.dct[i << 1]] > val:
                s, t, i = s, m, i << 1
            else:
                pre_sum += self.sum[self.dct[i << 1]]
                s, t, i = m + 1, t, (i << 1) | 1
        if t == self.n - 1 and self.range_pre_sum_max(self.n - 1) <= val:
            return t + 1
        return t



class Solution:
    def __init__(self):
        return
 
    @staticmethod
    def library_check_38(ac=FastIO()):
        """
        url: https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/F
        tag: segment_tree_dynamic|range_set|range_sum_bisect_left
        """
        n = ac.read_int()
        tree = RangeSetPreSumMaxDynamicDct(n, 10 ** 5, -1 << 32)
        while True:
            lst = ac.read_list_strs()
            if lst[0] == "I":
                ll, rr, hh = [int(w) for w in lst[1:]]
                tree.range_set(ll - 1, rr - 1, hh)
            elif lst[0] == "Q":
                hh = int(lst[1])
                ans = tree.range_pre_sum_max_bisect_left(hh)
                ac.st(ans)
            else:
                break
        return

    # @staticmethod
    # def main(ac=FastIO()):
    #     library_check_38(ac)
 
Solution().library_check_38()
