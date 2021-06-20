#include "base.h"

class Solution {
 public:
  string replaceSpaces(string S, int length) {
    if (length == 0) return S;

    int num = 0;
    int len = length - 1;

    while (len >= 0) {
      if (S[len] == ' ') {
        num++;
      }
      len--;
    }

    len = length + num * 2 - 1;
    S.resize(length + num * 2);
    int realLast = length - 1;

    while (realLast >= 0) {
      if (S[realLast] == ' ') {
        S[len] = '0';
        S[len - 1] = '2';
        S[len - 2] = '%';
        len -= 3;
      } else {
        S[len] = S[realLast];
        len -= 1;
      }
      realLast--;
    }
    return S;
  }
};

int main() {
  TEST_SMP2(Solution, replaceSpaces, string("Mr%20John%20Smith"),
            string("Mr John Smith    "), 13);
  TEST_SMP2(Solution, replaceSpaces, string("%20%20%20%20%20"),
            string("               "), 5);
  TEST_SMP2(Solution, replaceSpaces,
            string("ds%20sdfs%20afs%20sdfa%20dfssf%20asdf"),
            string("ds sdfs afs sdfa dfssf asdf             "), 27);

  return 0;
}
