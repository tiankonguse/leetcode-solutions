package Coding190429;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

/**
 * @author josonlee 
 * Topic1：https://leetcode-cn.com/problems/two-sum/
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标
 * 
 * Topic167：https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/
 * 给定一个已按照升序排列的有序数组，找到两个数使得它们相加之和等于目标数。 函数应该返回这两个下标值 index1 和 index2，其中
 * index1 必须小于 index2
 * 
 * Topic657:https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/
 * 给定一个二叉搜索树和一个目标结果，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 true。
 */
public class twoSum {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] num = { 2, 7, 11, 15 };
		System.out.println(Arrays.toString(solution1(num, 9)));
		System.out.println(Arrays.toString(solution2(num, 9)));
	}
	//用HashMap保存每次访问的数和下标，判断target-arr[i]是否在HashMap中
	public static int[] solution1(int[] nums, int target) {
		int[] arr = new int[2];
		HashMap<Integer, Integer> map = new HashMap();
		for (int i = 0; i < nums.length; i++) {
			if (map.containsKey(target - nums[i])) {
				arr[0] = map.get(target - nums[i]);
				arr[1] = i;
				break;
			} else {
				map.put(nums[i], i);
			}
		}
		return arr;
	}
	//因为是排序的arr，所以前后遍历大小关系可以可控制下标移动
	public static int[] solution2(int[] nums, int target) {
		int[] arr = new int[2];
		if (arr == null || arr.length == 0)
			return arr;
		Arrays.sort(nums);
		int i = 0, j = nums.length - 1;
		while (i < j) {
			int tmp = nums[i] + nums[j];
			if (tmp == target) {
				arr[0] = i;
				arr[1] = j;
				break;
			} else if (tmp > target) {
				j--;
			} else {
				i++;
			}
		}
		return arr;
	}

	class TreeNode {
		int val;
		TreeNode left;
		TreeNode right;
		TreeNode(int x) {
			val = x;
		}
	}
	private static HashSet<Integer> set = new HashSet<>();
	public static boolean findTarget(TreeNode root,int k) {
		//遍历BST，还是用HashSet存储遍历过的val，判断k-val在HashSet中否
        if(root==null)
            return false;
        if(set.contains(k-root.val))
            return true;
        set.add(root.val);
        return findTarget(root.left,k)||findTarget(root.right,k);
	}
}
