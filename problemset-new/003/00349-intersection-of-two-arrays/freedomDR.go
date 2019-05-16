package main

import "fmt"

func intersection(nums1 []int, nums2 []int) []int {
	s1 := make(map[int]int)
	s2 := make(map[int]int)
	for _, v := range nums1 {
		s1[v]++
	}
	for _, v := range nums2 {
		s2[v]++
	}
	res := make([]int, 0)
	for i := range s1 {
		if s2[i] != 0 {
			res = append(res, i)
		}
	}
	return res
}

func main() {
	fmt.Println("vim-go")
}
