// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Cashier {
  ll discount;
  int n;
  int index = 0;
  unordered_map<ll, ll> m;

 public:
  Cashier(int n_, int discount_, vector<int>& products, vector<int>& prices) {
    for (int i = 0; i < products.size(); i++) {
      m[products[i]] = prices[i];
    }
    discount = discount_;
    n = n_;
    index = 0;
  }

  double getBill(const vector<int>& product, const vector<int>& amount) {
    index++;
    double x = 0;
    for (int i = 0; i < product.size(); i++) {
      x += m[product[i]] * amount[i];
    }
    if (index % n == 0) {
      x = x - (discount * x) / 100.0;
    }
    return x;
  }
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */
