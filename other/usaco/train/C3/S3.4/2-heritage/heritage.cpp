/*
ID: tiankonguse
TASK: heritage
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "heritage"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
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

char inOrder[33];
char preOrder[33];
char postOrder[33];
int inIndex[33];
int n;

void Dfs(int inL, int inR, int preL, int preR, int postL, int postR) {
//   printf("root=%c in[%d,%d] pre[%d,%d] post[%d,%d]\n", preOrder[preL], inL,
//          inR, preL, preR, postL, postR);
  const char rootVal = preOrder[preL];
  postOrder[postR] = rootVal;

  const int inRoot = inIndex[rootVal - 'A'];
  const int leftLen = inRoot - inL;
  const int rightLen = inR - inRoot;

  if (leftLen > 0) {
    const int leftIn = inL;
    const int leftPre = preL + 1;
    const int leftPost = postL;
    Dfs(leftIn, leftIn + leftLen - 1,    //
        leftPre, leftPre + leftLen - 1,  //
        leftPost, leftPost + leftLen - 1);
  }
  if (rightLen > 0) {
    const int rightIn = inRoot + 1;
    const int rightPre = preR - rightLen + 1;
    const int rightPost = postR - rightLen;
    Dfs(rightIn, rightIn + rightLen - 1,    //
        rightPre, rightPre + rightLen - 1,  //
        rightPost, rightPost + rightLen - 1);
  }
}

void Solver() {  //
  scanf("%s", inOrder);
  scanf("%s", preOrder);
  n = strlen(inOrder);
  for (int i = 0; i < n; i++) {
    inIndex[inOrder[i] - 'A'] = i;
  }
  postOrder[n] = '\0';
  Dfs(0, n - 1, 0, n - 1, 0, n - 1);
  printf("%s\n", postOrder);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/