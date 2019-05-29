package main

import "fmt"

type NumArray struct {
	arr []int
}

func Constructor(nums []int) NumArray {
	arr := make([]int, len(nums)+1)
	for i := 0; i < len(nums); i++ {
		arr[i+1] = nums[i] + arr[i]
	}
	return NumArray{arr}
}

func (this *NumArray) SumRange(i int, j int) int {
	return this.arr[j+1] - this.arr[i]
}

/**
 * Your NumArray object will be instantiated and called as such:
 * obj := Constructor(nums);
 * param_1 := obj.SumRange(i,j);
 */
func main() {
	fmt.Println("vim-go")
}
