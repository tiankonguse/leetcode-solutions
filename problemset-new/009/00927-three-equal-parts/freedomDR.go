package main

import "fmt"

//玄学，同样的代码提交了三次才通过
func threeEqualParts(A []int) []int {
	sumsA := make([]int, len(A))
	sumsA[0] = A[0]
	for i := 1; i < len(A); i++ {
		sumsA[i] = sumsA[i-1] + A[i]
	}
	if sumsA[len(A)-1]%3 != 0 {
		return []int{-1, -1}
	}
	i1, i2 := 0, 0
	lo, hi := 0, len(A)
	t := sumsA[len(A)-1] / 3
	for lo < hi {
		mid := lo + (hi-lo)/2
		if sumsA[mid] <= t {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	i1 = lo - 1
	lo, hi = i1, len(A)
	t *= 2
	for lo < hi {
		mid := lo + (hi-lo)/2
		if sumsA[mid] <= t {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	i2 = lo - 1
	if i1 == i2 {
		return []int{0, 2}
	}
	finalZero := 0
	for p := len(A) - 1; A[p] == 0; p-- {
		finalZero++
	}
	p2Zero := 0
	for p := i2; A[p] == 0; p-- {
		p2Zero++
	}
	if p2Zero < finalZero {
		return []int{-1, -1}
	} else {
		i2 = i2 - (p2Zero - finalZero)
	}
	p1Zero := 0
	for p := i1; A[p] == 0; p-- {
		p1Zero++
	}
	if p1Zero < finalZero {
		return []int{-1, -1}
	} else {
		i1 = i1 - (p1Zero - finalZero)
	}
	for p, p1, p2, p3 := sumsA[len(A)-1]/3, i1, i2, len(A)-1; p != 0; {
		sums := A[p1] + A[p2] + A[p3]
		if sums == 3 {
			p--
			p1--
			p2--
			p3--
		} else if sums%3 != 0 {
			return []int{-1, -1}
		} else {
			p1--
			p2--
			p3--
		}
	}
	return []int{i1, i2 + 1}
}
func main() {
}
