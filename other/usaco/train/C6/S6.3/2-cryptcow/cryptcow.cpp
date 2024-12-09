/*
ID: tiankonguse
TASK: cryptcow
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "cryptcow"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const string base = "Begin the Escape execution at the Break of Dawn";
unordered_map<char, ll> charSet;
unordered_set<ll> H;
int BASE = 1;
int N;

ll Hash(ll pre, char c) { return (pre * BASE + charSet[c]) % mod; }

void Init() {
  charSet['C'] = 0;
  charSet['O'] = 0;
  charSet['W'] = 0;
  for (auto c : base) {
    charSet[c] = 0;
  }
  for (auto& [c, i] : charSet) {
    i = BASE++;
  }

  N = base.size();
  for (int i = 0; i < N; i++) {
    ll pre = 0;
    for (int j = i; j < N; j++) {
      const char c = base[j];
      pre = Hash(pre, c);
      H.insert(pre);
    }
  }
}

inline bool IsCow(char c) { return c == 'C' || c == 'O' || c == 'W'; }

int num = 0;
bool StatCheck(const char* buffer, const int len) {
  int C = 0, O = 0, W = 0;
  string baseStr = base, tmpStr;
  tmpStr.reserve(len);

  for (int i = 0; i < len; i++) {
    const char c = buffer[i];
    if (IsCow(c)) {
      if (c == 'C') {
        C++;
      } else if (c == 'O') {
        O++;
      } else if (c == 'W') {
        W++;
      }
    } else {
      tmpStr.push_back(c);
    }
  }
  sort(baseStr.begin(), baseStr.end());
  sort(tmpStr.begin(), tmpStr.end());
  if (baseStr != tmpStr) return false;
  if (C != O || C != W) return false;
  num = W;
  return true;
}

int tmpHash = 0;
inline bool CheckHash(const char* buffer, const int len) {
  ll pre = 0;
  tmpHash = 0;
  for (int i = 0; i < len; i++) {
    const char c = buffer[i];
    tmpHash = Hash(tmpHash, c);
    if (IsCow(c)) {
      pre = 0;
    } else {
      pre = Hash(pre, c);
      if (!H.count(pre)) return false;
    }
  }
  return true;
}

unordered_set<ll> matchHash[49][49][11];
bool Match(const char* buffer, const int L, const int R, const int len,
           const int k);

bool Judge(const char* buffer, const int L, const int R, const int len,
           const int k, const int ci, const int oi, const int wi) {
  string tmpBuf;
  tmpBuf.reserve(len - 3);
  for (int i = 0; i < ci; i++) {  // 剪枝：前后缀匹配时，可以忽略前后缀
    tmpBuf.push_back(buffer[i]);
  }
  for (int i = oi + 1; i < wi; i++) {  // skip O
    tmpBuf.push_back(buffer[i]);
  }
  for (int i = ci + 1; i < oi; i++) {  // skip C
    tmpBuf.push_back(buffer[i]);
  }
  for (int i = wi + 1; i < len; i++) {  // skip W
    tmpBuf.push_back(buffer[i]);
  }

  int l = 0, r = tmpBuf.size();
  int eqL = 0, eqR = 0;
  while (l < r && tmpBuf[l] == base[L + eqL]) {
    l++;
    eqL++;
  }
  while (l < r && tmpBuf[r - 1] == base[R - 1 - eqR]) {
    r--;
    eqR++;
  }
  if (l == r) return true;
  if (l < r && !IsCow(tmpBuf[l])) return false;
  if (l < r && !IsCow(tmpBuf[r - 1])) return false;
  if (tmpBuf[l] != 'C') return false;
  if (tmpBuf[r - 1] != 'W') return false;

  return Match(tmpBuf.data() + l, L + eqL, R - eqR, r - l, k - 1);
}

bool Match(const char* buffer, const int L, const int R, const int len,
           const int k) {  // [L, R)
  if (!CheckHash(buffer, len)) return false;
  if (k == 0) return true;

  if (matchHash[L][R][k].count(tmpHash)) return false;
  matchHash[L][R][k].insert(tmpHash);

  for (int oi = 0; oi < len; oi++) {
    if (buffer[oi] != 'O') continue;
    for (int ci = 0; ci < oi; ci++) {
      if (buffer[ci] != 'C') continue;
      for (int wi = len - 1; wi > oi; wi--) {
        if (buffer[wi] != 'W') continue;
        if (Judge(buffer, L, R, len, k, ci, oi, wi)) {
          return true;
        }
      }
    }
  }
  return false;
}

pair<int, int> Solver(const char* buffer, const int len) {
  if (!StatCheck(buffer, len)) {
    printf("StatCheck No\n");
    return {0, 0};
  }
  if (Match(buffer, 0, N, len, num)) {
    return {1, num};
  }
  return {0, 0};
}

void Solver() {  //
  const int bufsize = 100;
  char buffer[bufsize];
  fgets(buffer, bufsize, stdin);
  Init();
  int l = strlen(buffer);
  buffer[l - 1] = '\0';
  auto [ok, num] = Solver(buffer, l - 1);
  printf("%d %d\n", ok, num);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.007 secs limit:2s, 3572 KB]
   Test 2: TEST OK [0.011 secs limit:2s, 3696 KB]
   Test 3: TEST OK [0.011 secs limit:2s, 3552 KB]
   Test 4: TEST OK [0.007 secs limit:2s, 3584 KB]
   Test 5: TEST OK [0.007 secs limit:2s, 3692 KB]
   Test 6: TEST OK [0.084 secs limit:2s, 3708 KB]
   Test 7: TEST OK [0.011 secs limit:2s, 3696 KB]
   Test 8: TEST OK [0.063 secs limit:2.5s, 3596 KB]
   Test 9: TEST OK [1.004 secs limit:2s, 4056 KB]
   Test 10: TEST OK [1.505 secs limit:2s, 4084 KB]

All tests OK.
*/