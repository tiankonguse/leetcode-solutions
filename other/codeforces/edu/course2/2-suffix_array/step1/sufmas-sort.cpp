// https://codeforces.com/edu/course/2/lesson/2/1

// O(Nlog^2N)
// using standrad std::sort algorithm ,O(N logN)

#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;
  s += "$";
  int n = s.size();
  vector<int> p(n), c(n);
  {
    // k = 0
    vector<pair<char, int>> a(n);
    // save characters and positions then sort
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());

    // save array [p]
    for (int i = 0; i < n; ++i) p[i] = a[i].second;
    // create array [c]
    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (a[i].first == a[i - 1].first) {
        c[p[i]] = c[p[i - 1]];
      } else {
        c[p[i]] = c[p[i - 1]] + 1;
      }
    }
  }
  // now transitions of k
  int k = 0;
  while ((1 << k) < n) {
    // k -> K + 1
    // 2 eqvalence classes for left and right part , and index of string
    vector<pair<pair<int, int>, int>> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
    }
    // follow the approach for k = 0
    sort(a.begin(), a.end());
    // save array [p]
    for (int i = 0; i < n; ++i) p[i] = a[i].second;
    // create array [c]
    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (a[i].first == a[i - 1].first) {
        c[p[i]] = c[p[i - 1]];
      } else {
        c[p[i]] = c[p[i - 1]] + 1;
      }
    }
    k++;
  }
  // testing
  for (int i = 0; i < n; ++i) {
    cout << p[i] << " " << s.substr(p[i], n - p[i]) << "\n";
    // cout << p[i] << "\n";
  }
}