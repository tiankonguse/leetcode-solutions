#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> H0;
vector<ll> H1;
void Init() {
  H0.push_back(0);
  for (int i = 1; i <= 13; i += 2) {
    H0.push_back(i);
  }
  for (int i = 2; i <= 13; i += 2) {
    H0.push_back(i);
  }
  H1.push_back(0);
  for (int i = 2; i <= 13; i += 2) {
    H1.push_back(i);
  }
  for (int i = 1; i <= 13; i += 2) {
    H1.push_back(i);
  }
}

ll Solver0(ll N);
ll Solver1(ll N);

ll Solver0(ll N) {  // 1 不选择
  if (N == 1) return 1;
  if (N % 2 == 0) {
    return H0[Solver0(N / 2)];
  } else {
    return H0[Solver1(N / 2 + 1)];
  }
}

ll Solver1(ll N) {  // 1 选择
  if (N == 1) return 1;
  if (N % 2 == 0) {
    return H1[Solver1(N / 2)];
  } else {
    return H1[Solver0(N / 2)];
  }
}

int main() {
  Init();
//   for (ll i = 1; i <= 30; i++) {
//     printf("i=%lld skip1=%lld noskip1=%lld\n", i, Solver0(i), Solver1(i));
//   }
  ll N;
  scanf("%lld", &N);
  printf("%lld\n", Solver0(N));
  return 0;
}