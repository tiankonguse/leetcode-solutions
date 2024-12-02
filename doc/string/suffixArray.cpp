
#ifndef SPARSETABLE_H_
#define SPARSETABLE_H_

#include <algorithm>
#include <cassert>
#include <vector>

namespace data_structure {
// 0-indexed sparse table.
// Operation can be:
//    decltype(std::max), decltype(std::min), decltype(std::gcd)
template <typename ValueType, typename Operation>
class SparseTable {
 private:
  std::vector<std::vector<ValueType>> table;
  Operation operation;

 public:
  template <typename InputIt>
  explicit SparseTable(InputIt first, InputIt last, const Operation& operation)
      : operation(operation) {
    int size = last - first;
    assert(size >= 1);
    int log = bit_lg(size);
    table = std::vector<std::vector<ValueType>>(log + 1,
                                                std::vector<ValueType>(size));
    std::copy(first, last, table[0].begin());
    for (int k = 1; k <= log; ++k)
      for (int i = 0; i < size; ++i)
        if (int j = i + (1 << (k - 1)); j < size)
          table[k][i] = operation(table[k - 1][i], table[k - 1][j]);
  }
  ValueType Query(int x, int y) const  // [x, y)
  {
    assert(x < y);
    int k = bit_lg(y - x);
    return operation(table[k][x], table[k][y - (1 << k)]);
  }
};
}  // namespace data_structure

#endif

#ifndef SUFFIXARRAY_H_
#define SUFFIXARRAY_H_

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

namespace algorithm {
// The current implementation of SuffixArray is based on:
// [NZC09] G. Nong, S. Zhang and W. H. Chan. Linear suffix array construction by
// almost pure induced-sorting. 2009 Data Compression Conference, pp. 193-202.
// 2009 sa[0], ..., sa[n-1] is a permutation of 0 to n-1 such that
//     suffix(data, sa[i]) < suffix(data, sa[i+1])
// for every 0 <= i < n-2.
// height[i] = LCP(suffix(data, sa[i]), suffix(data, sa[i+1])), where LCP stands
// for Longest Common Prefix.
class SuffixArray {
 private:
  std::vector<int> sa, height, rank, bucket, guard;
  void SAIS(int n, int num_alpha, int* data, int* type, int* lms) {
    int new_n = 0;
    // The type of position i is S-type, i.e. type[i] = 0, if suffix(data, i) <
    // suffix(data, i + 1). The type of position i is L-type, i.e. type[i] = 1,
    // if suffix(data, i) > suffix(data, i + 1).
    type[n - 1] = 0;
    for (int i = n - 2; i >= 0; --i)
      type[i] = data[i] == data[i + 1] ? type[i + 1] : data[i] > data[i + 1];

    // lms stands for leftmost S-type.
    this->rank[0] = -1;  // lms type never occurs at position 0.
    for (int i = 1; i < n; ++i) {
      if (type[i - 1] == 1 && type[i] == 0) {
        lms[new_n] = i;
        this->rank[i] = new_n;
        new_n += 1;
      } else
        this->rank[i] = -1;
    }

    auto InducedSort = [&](int* v) {
      std::fill_n(this->sa.begin(), n, -1);
      std::fill_n(this->bucket.begin(), num_alpha, 0);
      for (int i = 0; i < n; ++i) this->bucket[data[i]] += 1;
      for (int i = 1; i < num_alpha; ++i)
        this->bucket[i] += this->bucket[i - 1];

      std::copy_n(this->bucket.begin(), num_alpha, this->guard.begin());
      for (int i = new_n - 1; i >= 0; --i)
        this->sa[--this->guard[data[v[i]]]] = v[i];

      std::copy_n(this->bucket.begin(), num_alpha - 1, this->guard.begin() + 1);
      for (int i = 0; i < n; ++i)
        if (this->sa[i] > 0 && type[this->sa[i] - 1] == 1)
          this->sa[this->guard[data[this->sa[i] - 1]]++] = this->sa[i] - 1;

      std::copy_n(this->bucket.begin(), num_alpha, this->guard.begin());
      for (int i = n - 1; i >= 0; --i)
        if (this->sa[i] > 0 && type[this->sa[i] - 1] == 0)
          this->sa[--this->guard[data[this->sa[i] - 1]]] = this->sa[i] - 1;
    };

    InducedSort(lms);

    int* new_data = data + n;
    int alpha = -1;
    for (int i = 0, y = -1; i < n; ++i) {
      int x = this->rank[this->sa[i]];
      if (x != -1) {
        if (alpha < 1 || lms[x + 1] - lms[x] != lms[y + 1] - lms[y])
          alpha += 1;
        else {
          for (int a = lms[x], b = lms[y]; a <= lms[x + 1]; ++a, ++b)
            if (data[a] != data[b] || type[a] != type[b]) {
              alpha += 1;
              break;
            }
        }
        new_data[x] = alpha;
        y = x;
      }
    }

    if (alpha + 1 < new_n)
      this->SAIS(new_n, alpha + 1, new_data, type + n, lms + new_n);
    else {
      for (int i = 0; i < new_n; ++i) this->sa[new_data[i]] = i;
    }
    for (int i = 0; i < new_n; ++i) new_data[i] = lms[this->sa[i]];

    InducedSort(new_data);
  }
  void Init(std::vector<int>& data, int num_alpha) {
    int n = data.size();
    data.resize(n * 2);
    std::vector<int> type(n * 2);
    std::vector<int> lms(n);
    this->sa = std::vector<int>(n);
    this->rank = std::vector<int>(n);
    this->bucket = std::vector<int>(std::max(n, num_alpha));
    this->guard = std::vector<int>(std::max(n, num_alpha));
    this->SAIS(n, num_alpha, data.data(), type.data(), lms.data());

    // remove the end mask.
    n -= 1;
    for (int i = 0; i < n; ++i) this->sa[i] = this->sa[i + 1];
    this->sa.pop_back();

    this->height = std::vector<int>(n - 1);
    for (int i = 0; i < n; ++i) this->rank[this->sa[i]] = i;
    for (int i = 0, h = 0; i < n - 1; ++i) {
      if (this->rank[i] > 0) {
        int j = this->sa[this->rank[i] - 1];
        while (i + h < n && j + h < n && data[i + h] == data[j + h]) ++h;
        this->height[this->rank[i] - 1] = h;
        h = std::max(h - 1, 0);
      }
    }
  }
  static constexpr auto min =
      static_cast<const int& (*)(const int&, const int&)>(&std::min<int>);
  using RangeMinQuery = data_structure::SparseTable<int, decltype(min)>;
  RangeMinQuery* rmq;

 public:
  SuffixArray(const std::vector<int>& data, int num_alpha) : rmq(nullptr) {
    for (auto& x : data) assert(0 <= x && x < num_alpha);
    int n = data.size();
    std::vector<int> s_data(n + 1);
    std::copy_n(data.begin(), n, s_data.begin());
    for (auto& x : s_data) x += 1;
    this->Init(s_data, num_alpha);
  }
  SuffixArray(const std::string& data) : rmq(nullptr) {
    int n = data.size();
    std::vector<int> s_data(n + 1);
    for (int i = 0; i < n; ++i) s_data[i] = data[i] + 1;
    this->Init(s_data, 255);
  }
  ~SuffixArray() {
    if (rmq != nullptr) delete rmq;  // remember to delelte this pointer
  }
  const std::vector<int>& GetSuffixArray() { return this->sa; }
  const std::vector<int>& GetHeight() { return this->height; }
  // Return the Longest Common Prefix of suffix(data, x) and suffix(data, y).
  int LongestCommonPrefix(int x, int y) {
    assert(0 <= x && x < (int)sa.size() && 0 <= y && y < (int)sa.size());
    if (x == y) return (int)sa.size() - x;
    x = rank[x], y = rank[y];
    if (x > y) std::swap(x, y);
    if (rmq == nullptr)
      rmq = new RangeMinQuery(height.begin(), height.end(), min);
    return rmq->Query(x, y);
  }
};
}  // namespace algorithm

#endif