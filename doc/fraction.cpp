namespace MATH {

typedef pair<int, int> Fraction;

bool Zero(const Fraction& l) { return l.first == 0; }
Fraction Sample(int A, int B) {
  if (A == 0) {
    return Fraction{0, 1};
  }

  if (B < 0) {
    A = -A;
    B = -B;
  }

  int sign = 1;
  if (A < 0) {
    sign = -1;
    A = -A;
  }

  int G = Gcd(A, B);
  A = A / G;
  B = B / G;
  return Fraction{sign * A, B};
}

Fraction operator+(const Fraction& l, const Fraction& r) {
  int A = l.first * r.second + r.first * l.second;
  int B = l.second * r.second;
  return Sample(A, B);
}

Fraction operator-(const Fraction& l, const Fraction& r) {
  int A = l.first * r.second - r.first * l.second;
  int B = l.second * r.second;
  return Sample(A, B);
}

Fraction operator*(const Fraction& l, const Fraction& r) {
  int A = l.first * r.first;
  int B = l.second * r.second;
  return Sample(A, B);
}

Fraction operator/(const Fraction& l, const Fraction& r) {
  int A = l.first * r.second;
  int B = l.second * r.first;
  return Sample(A, B);
}
};  // namespace MATH