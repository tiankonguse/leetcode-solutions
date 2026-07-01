
struct BigNum {
  vector<ll> data;  // 逆序存储
  BigNum() {}
  BigNum(ll x) {
    while (x) {
      data.push_back(x % 10);
      x /= 10;
    }
    if (data.empty()) {
      data.push_back(0);
    }
  }
  BigNum(const string& s) {
    for (int i = s.size() - 1; i >= 0; i--) {
      data.push_back(s[i] - '0');
    }
  }
  BigNum& Smp() {
    while (data.size() > 1 && data.back() == 0) {
      data.pop_back();
    }
    return *this;
  }
  BigNum& Append(ll x) {
    data.push_back(x);
    return Smp();
  }
  BigNum operator*(const BigNum& other) const {
    BigNum res;
    res.data.resize(data.size() + other.data.size() + 1, 0);
    for (int i = 0; i < data.size(); i++) {
      int carry = 0;
      int pos = i;
      for (int j = 0; j < other.data.size(); j++) {
        res.data[pos] += data[i] * other.data[j] + carry;
        carry = res.data[pos] / 10;
        res.data[pos] %= 10;
        pos++;
      }
      while (carry) {
        res.data[pos] += carry;
        carry = res.data[pos] / 10;
        res.data[pos] %= 10;
        pos++;
      }
    }
    return res.Smp();
  }
  bool operator<(const BigNum& other) const {
    if (data.size() != other.data.size()) {
      return data.size() < other.data.size();
    }
    for (int i = data.size() - 1; i >= 0; i--) {
      if (data[i] != other.data[i]) {
        return data[i] < other.data[i];
      }
    }
    return false;
  }
  string ToString() const {
    string res;
    for (int i = data.size() - 1; i >= 0; i--) {
      res.push_back(data[i] + '0');
    }
    return res;
  }
};