
typedef long long ll;
const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 100010, max6 = 2000010;

const ll BASE = 29, BASE1 = 100003, BASE2 = 100019;

class StringHash {
  ll h[max5];
  ll qpowCache[max5];
  const ll BASE;
  const ll MOD;

 public:
  StringHash(ll base, ll mod) : BASE(base), MOD(mod) {}
  ll H(int l, int r) { // [l,r], 0 base
    if (l == 0) return h[r];
    ll pre = h[l - 1] * qpowCache[r - l + 1] % MOD;
    return (h[r] - pre + MOD) % MOD;
  }

  void Init(const vector<int>& str, int n) {
    qpowCache[0] = 1;
    for (int i = 1; i <= n; i++) {
      qpowCache[i] = (qpowCache[i - 1] * BASE) % MOD;
    }

    ll pre = 0;
    for (int i = 0; i < n; i++) {
      pre = (pre * BASE + str[i]) % MOD;
      h[i] = pre;
    }
  }
  void Init(const string& str, int n) {
    qpowCache[0] = 1;
    for (int i = 1; i <= n; i++) {
      qpowCache[i] = (qpowCache[i - 1] * BASE) % MOD;
    }

    ll pre = 0;
    for (int i = 0; i < n; i++) {
      pre = (pre * BASE + str[i] - '0' + 1) % MOD;
      h[i] = pre;
    }
  }
};

StringHash H1(BASE1, mod1e7);
StringHash H2(BASE2, mod1e9);