class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        n, bound = len(arr), bisect.bisect_right(arr, x)
        left, right = bound - 1, bound
        for i in range(k):
            if left >= 0 and right < n:
                if x - arr[left] <= arr[right] - x:
                    left -= 1
                else:
                    right += 1
            elif right < n:
                right += 1
            else:
                left -= 1
        return arr[left + 1:right]
