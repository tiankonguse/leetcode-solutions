class Solution:
    def search(self, nums: List[int], target: int) -> int:
        low, high = 0, len(nums) - 1
        while low <= high:
            mid = (low + high) >> 1
            if nums[mid] == target:
                return mid
            if nums[low] > nums[mid]:
                if nums[mid] < target < nums[low]:
                    low = mid + 1
                else:
                    high = mid - 1
            else:
                if nums[low] <= target < nums[mid]:
                    high = mid - 1
                else:
                    low = mid + 1
        return -1
