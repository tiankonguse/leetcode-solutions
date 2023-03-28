// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  void Dump(string s, vector<ll>& a) {
    printf("%s(%d): ", s.c_str(), a.size());
    for (auto v : a) {
      printf("%lld ", v);
    }
    printf("\n");
  }
  // {a1 * a2, b1*b2}, 求第 k 大数字
  ll Solver(vector<ll>& a1, vector<ll>& a2, vector<ll>& b1, vector<ll>& b2,
            ll k) {
    // printf("k=%lld\n", k);
    // Dump("a1", a1);
    // Dump("a2", a2);
    // Dump("b1", b1);
    // Dump("b2", b2);
    ll l = 1, r = 2;  //[l, r)
    if (a1.size() && a2.size()) {
      r = max(r, a1.back() * a2.back()) + 1;
    }
    if (b1.size() && b2.size()) {
      r = max(r, b1.back() * b2.back()) + 1;
    }

    while (l < r) {
      ll mid = (l + r) / 2;

      ll num = 0;
      if (a1.size() && a2.size()) {
        for (ll a : a1) {
          ll b = mid / a;
          num += upper_bound(a2.begin(), a2.end(), b) - a2.begin();
        }
      }
      if (b1.size() && b2.size()) {
        for (ll a : b1) {
          ll b = mid / a;
          num += upper_bound(b2.begin(), b2.end(), b) - b2.begin();
        }
      }

      if (num < k) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }

    return l;
  }

 public:
  long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2,
                               long long k) {
    vector<ll> neg1, neg2, one1, one2;
    ll zero1 = 0, zero2 = 0;
    sort(nums1.begin(), nums1.end());
    for (ll v : nums1) {
      if (v < 0) {
        neg1.push_back(-v);
      } else if (v > 0) {
        one1.push_back(v);
      } else {
        zero1++;
      }
    }
    std::reverse(neg1.begin(), neg1.end());

    sort(nums2.begin(), nums2.end());
    for (ll v : nums2) {
      if (v < 0) {
        neg2.push_back(-v);
      } else if (v > 0) {
        one2.push_back(v);
      } else {
        zero2++;
      }
    }
    std::reverse(neg2.begin(), neg2.end());

    ll negNum1 = neg1.size(), negNum2 = neg2.size();
    ll oneNum1 = one1.size(), oneNum2 = one2.size();
    ll negNum = negNum1 * oneNum2 + negNum2 * oneNum1;
    ll zeroNum = zero1 * nums2.size() + zero2 * nums1.size() - zero1 * zero2;

    if (k <= negNum) {
      k = negNum - k + 1;
      return -Solver(neg1, one2, neg2, one1, k);
    } else if (k > negNum + zeroNum) {
      k = k - negNum - zeroNum;
      return Solver(one1, one2, neg1, neg2, k);
    } else {
      return 0;
    }
  }
};
