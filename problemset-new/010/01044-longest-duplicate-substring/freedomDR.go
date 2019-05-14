package main

import "fmt"

const mod = 1e9 + 7

func check(S string, sLen int) int {
	s := make(map[int][]int)
	base, value := 1, 0
	for i := 0; i < sLen; i++ {
		value = value*26 + int(S[i]-'a')
		value = value % mod
		base = base * 26
		base %= mod
	}
	s[value] = append(s[value], 0)
	for i := sLen; i < len(S); i++ {
		value = value*26 + int(S[i]-'a') - int(S[i-sLen]-'a')*base
		for value < 0 {
			value += mod
		}
		value %= mod
		if len(s[value]) != 0 {
			for _, pos := range s[value] {
				if S[i-sLen+1:i+1] == S[pos:pos+sLen] {
					return i - sLen + 1
				}
			}
		}
		s[value] = append(s[value], i-sLen+1)
	}
	return -1
}

func longestDupSubstring(S string) string {
	st, sLen := 0, 0
	lo, hi := 1, len(S)
	for lo < hi {
		mid := lo + (hi-lo)/2
		res := check(S, mid)
		if res != -1 {
			st = res
			sLen = mid
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return S[st : st+sLen]
}

func main() {
	fmt.Println("vim-go")
}
