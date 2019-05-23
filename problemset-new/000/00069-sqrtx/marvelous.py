class Solution:
    def mySqrt(self, x: int) -> int:
        left, right = 0, x
        while left <= right:
            mid = (left + right) >> 1
            if mid ** 2 <= x:
                left = mid + 1
            else:
                right = mid - 1
        return right
