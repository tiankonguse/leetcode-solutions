# The guess API is already defined for you.
# @param num, your guess
# @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
# def guess(num):

class Solution(object):
    def guessNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        left, right = 1, n
        while left <= right:
            mid = (left + right) >> 1
            state = guess(mid)
            if state == 0:
                return mid
            elif state == -1:
                right = mid - 1
            else:
                left = mid + 1
