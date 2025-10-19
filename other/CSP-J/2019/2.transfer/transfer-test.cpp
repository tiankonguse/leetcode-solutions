/*
ID: tiankonguse
TASK: transfer
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P5661
PATH:  P5661 [CSP-J2019] 公交换乘
submission:
*/
#define TASK "transfer"
#define TASKEX "-test"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct RangeIterator {
  long long val;
  RangeIterator(long long v) : val(v) {}
  long long operator*() const { return val; }
  RangeIterator& operator++() {
    ++val;
    return *this;
  }
  RangeIterator& operator+=(long long __n) {
    val += __n;
    return *this;
  }
  bool operator!=(const RangeIterator& other) const { return val != other.val; }
  long long operator-(const RangeIterator& __y) const { return val - __y.val; }
};

template <>
struct iterator_traits<RangeIterator> {
  typedef long long difference_type;
  typedef random_access_iterator_tag iterator_category;
};
int main(int argc, char** argv) {

  vector<int> vecList = {1, 2, 3, 4, 5};
  int vecOffset= lower_bound(vecList.begin(), vecList.end(), 3) - vecList.begin();

  int arrList[] = {1, 2, 3, 4, 5};
  int arrOffset= lower_bound(arrList, arrList + 5, 3) - arrList;


  map<ll, ll> h = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  auto it = h.lower_bound(5);

  set<int> s = {1, 2, 3, 4, 5};
  auto it2 = s.lower_bound(3);


  auto Cmp = [&](const ll& mid, const ll& val) {  //
    return mid < val;
  };
  while (1) {
    ll p;
    scanf("%lld", &p);
    printf("upper_bound=%lld\n",*upper_bound(RangeIterator(0), RangeIterator(10000), p, Cmp));
    printf("lower_bound=%lld\n",*lower_bound(RangeIterator(0), RangeIterator(10000), p, Cmp));
  }



  return 0;
}
