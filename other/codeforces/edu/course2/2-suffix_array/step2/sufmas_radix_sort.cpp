// https://codeforces.com/edu/course/2/lesson/2/2

// O(2NlogN) ~ O(NlogN)
// using radix sort (2*counting sort)

#include <bits/stdc++.h>

using namespace std;

void radix_sort(vector<pair<pair<int, int>, int>> &a) {
  int n = a.size();
  // counting sort twice
  {
    vector<int> cnt(n);
    for (auto x : a) {
      cnt[x.first.second]++;
    }
    vector<pair<pair<int, int>, int>> a_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) {
      pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (auto x : a) {
      int i = x.first.second;
      a_new[pos[i]] = x;
      pos[i]++;
    }
    a = a_new;
  }
  {
    vector<int> cnt(n);
    for (auto x : a) {
      cnt[x.first.first]++;
    }
    vector<pair<pair<int, int>, int>> a_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) {
      pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (auto x : a) {
      int i = x.first.first;
      a_new[pos[i]] = x;
      pos[i]++;
    }
    a = a_new;
  }
}

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
    vector<pair<pair<int, int>, int>> a(n);  // 2 eqvalence classes for left and
                                             // right part , and index of string
    for (int i = 0; i < n; i++) {
      a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
    }
    // follow the approach for k = 0
    radix_sort(a);
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
    // cout << p[i] << " " << s.substr(p[i] ,n - p[i]) << "\n";
    cout << p[i] << "\n";
  }
}