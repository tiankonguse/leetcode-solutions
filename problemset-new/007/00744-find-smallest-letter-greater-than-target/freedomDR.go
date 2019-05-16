package main

import "fmt"

func nextGreatestLetter(letters []byte, target byte) byte {
	lo, hi := 0, len(letters)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if letters[mid] <= target {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	if lo == len(letters) {
		return letters[0]
	} else {
		return letters[lo]
	}
}
func main() {
	fmt.Println("vim-go")
}
