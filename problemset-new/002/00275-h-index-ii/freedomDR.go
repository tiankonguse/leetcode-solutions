package main

import "fmt"

//题意至多该改为至少
func hIndex(citations []int) int {
	n := 1
	for i := len(citations) - 1; i >= 0 && citations[i] >= n; {
		i--
		n++
	}
	return n - 1
}
func main() {
	fmt.Println("vim-go")
}
