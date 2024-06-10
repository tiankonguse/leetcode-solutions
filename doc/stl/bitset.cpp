#include <bits/stdc++.h>

const size_t N = 10e5;
bitset<N> flags;  // 初始化
flags.set(0);     // 某一位设置为 1
flags.test(i);    // 某一位是否是 1

// 23.3.5.2 bitset operations:
bitset& operator&=(const bitset& rhs) noexcept;  // constexpr since C++23
bitset& operator|=(const bitset& rhs) noexcept;  // constexpr since C++23
bitset& operator^=(const bitset& rhs) noexcept;  // constexpr since C++23
bitset& operator<<=(size_t pos) noexcept;        // constexpr since C++23
bitset& operator>>=(size_t pos) noexcept;        // constexpr since C++23
bitset& set() noexcept;                          // constexpr since C++23
bitset& set(size_t pos, bool val = true);        // constexpr since C++23
bitset& reset() noexcept;                        // constexpr since C++23
bitset& reset(size_t pos);                       // constexpr since C++23
bitset operator~() const noexcept;               // constexpr since C++23
bitset& flip() noexcept;                         // constexpr since C++23
bitset& flip(size_t pos);                        // constexpr since C++23

// element access:
constexpr bool operator[](size_t pos) const;
reference operator[](size_t pos);      // constexpr since C++23
unsigned long to_ulong() const;        // constexpr since C++23
unsigned long long to_ullong() const;  // constexpr since C++23

size_t count() const noexcept;                      // constexpr since C++23
constexpr size_t size() const noexcept;             // constexpr since C++23
bool operator==(const bitset& rhs) const noexcept;  // constexpr since C++23
bool operator!=(const bitset& rhs) const noexcept;  // removed in C++20
bool test(size_t pos) const;                        // constexpr since C++23
bool all() const noexcept;                          // constexpr since C++23
bool any() const noexcept;                          // constexpr since C++23
bool none() const noexcept;                         // constexpr since C++23
bitset<N> operator<<(size_t pos) const noexcept;    // constexpr since C++23
bitset<N> operator>>(size_t pos) const noexcept;    // constexpr since C++23