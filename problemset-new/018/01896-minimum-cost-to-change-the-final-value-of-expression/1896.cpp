// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
enum { ZERO = 0, ONE = 1, OR = 2, AND = 3 };
struct T {
  int type = 0;  // 1:01, 2:|, 3:&
  int l = 0;
  int r = 0;
  int val = 0;  // 运算结果
  int ans = 0;  //反转答案
} buf[max5];
class Solution {
  int index = 0;
  string exp;
  int n;
  int H() { return ++index; }

  int Parse(int& pos) {
    int start = pos;
    int l = 0, r = 0;

    if (exp[pos] == '(') {
      pos++;  // skip (
      l = Parse(pos);
      pos++;  // skip )
      // printf("(): l=%d v=%d [%d,%d] %s\n", l, buf[l].val, start, pos,
      //        exp.substr(start, pos - start).c_str());
    } else {  // '0' or '1'
      l = H();
      buf[l].type = exp[pos] - '0';
      buf[l].val = buf[l].type;
      pos++;  // skip val
    }

    if (pos == n || exp[pos] == ')') {
      // printf("parse h=%d v=%d [%d,%d) %s\n", l, buf[l].val, start, pos,
      //        exp.substr(start, pos - start).c_str());
      return l;
    }

    int t = 0;
    if (exp[pos] == '|') {
      t = OR;
    } else {
      t = AND;
    }
    pos++;  // skip '|' '&'

    r = Parse(pos);

    int h = H();
    buf[h].type = t;
    buf[h].l = l;
    buf[h].r = r;
    if (t == OR) {
      buf[h].val = buf[l].val || buf[r].val;
    } else {
      buf[h].val = buf[l].val && buf[r].val;
    }

    // printf("parse h=%d v=%d [%d,%d) %s\n", h, buf[h].val, start, pos,
    //        exp.substr(start, pos - start).c_str());
    return h;
  }
  int LV(int root) { return buf[buf[root].l].val; }
  int RV(int root) { return buf[buf[root].r].val; }
  int LA(int root) { return buf[buf[root].l].ans; }
  int RA(int root) { return buf[buf[root].r].ans; }

  int Dfs(int root) {
    T& t = buf[root];
    if (t.type == ZERO || t.type == ONE) {
      t.ans = 1;
    } else {
      Dfs(t.l);
      Dfs(t.r);

      if (t.type == OR) {  // |
        if (LV(root) == 0 && RV(root) == 0) {
          t.ans = min(LA(root), RA(root));
        } else if (LV(root) == 1 && RV(root) == 1) {
          t.ans = min(LA(root), RA(root)) + 1;
        } else {
          t.ans = 1;
        }

      } else {  // &
        if (LV(root) == 0 && RV(root) == 0) {
          // 0 & 0
          t.ans = min(LA(root), RA(root)) + 1;
        } else if (LV(root) == 1 && RV(root) == 1) {
          t.ans = min(LA(root), RA(root));
        } else {
          t.ans = 1;
        }
      }
    }
    return t.ans;
  }

 public:
  int minOperationsToFlip(string expression) {
    expression.swap(exp);
    std::reverse(exp.begin(), exp.end());
    for (auto& c : exp) {
      if (c == '(') {
        c = ')';
      } else if (c == ')') {
        c = '(';
      }
    }
    // printf("exp=%s\n", exp.c_str());
    n = exp.size();

    int pos = 0;
    int root = Parse(pos);
    // return root;
    return Dfs(root);
  }
};

int main() {
  int ans;
  string expression;

  ans = 1;
  expression = "1&(0|1)";
  TEST_SMP1(Solution, minOperationsToFlip, ans, expression);

  ans = 3;
  expression = "(0&0)&(0&0&0)";
  TEST_SMP1(Solution, minOperationsToFlip, ans, expression);

  ans = 1;
  expression = "(0|(1|0&1))";
  TEST_SMP1(Solution, minOperationsToFlip, ans, expression);
  return 0;
}