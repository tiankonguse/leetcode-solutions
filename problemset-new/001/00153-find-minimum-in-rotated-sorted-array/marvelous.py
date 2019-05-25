class Solution:
    def findMin(self, nums: List[int]) -> int:
        low, high = 0, len(nums) - 1
        # [a, b]
        while low < high:
            if nums[low] < nums[high]:
                return nums[low]
            mid = (low + high) >> 1
            if nums[mid] > nums[high]:
                low = mid + 1
            else:
                high = mid
        return nums[low]        
