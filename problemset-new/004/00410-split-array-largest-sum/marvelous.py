class Solution:
    @staticmethod
    def check(nums, m, at_most):
        slide, cnt = at_most + 1, 0
        for elem in nums:
            if elem > at_most:
                return False
            if slide + elem <= at_most:
                slide += elem
            else:
                slide = elem
                cnt += 1
        return cnt <= m
    
    def splitArray(self, nums: List[int], m: int) -> int:
        low, high = 0, sum(nums)
        while low < high:
            mid = (low + high) >> 1
            ok = self.check(nums, m, mid)
            if ok:
                high = mid
            else:
                low = mid + 1
        return high
