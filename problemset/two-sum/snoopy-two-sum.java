class Solution {
    
    public static void main (String args[]){
       int[] nums = {2, 7, 11, 15};
        int[] a =  twoSum(nums,9);
        for(int i = 0 ; i<a.length;i++){
            System.out.println(a[i]);
        }
    }
    
    public static int[] twoSum(int[] nums, int target) {
      
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }
            map.put(nums[i], i);
        }
        throw new IllegalArgumentException("No two sum solution");
    }
}
