/*
ID: tiankonguse
TASK: expr
LANG: C++
https://www.luogu.com.cn/problem/P8815
*/
#define TASK "expr"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
constexpr int INF = 1 << 30;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

using int128 = __int128;

void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "1"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

const int N = 1e6 + 10;
char str[N];
int n;
enum { E_NUM = 0, E_AND, E_OR };

struct Node {
  int ans = 0;
  int type = 0;
  vector<int> childs;
};
Node nodes[N];
int nodeIndex = 0;

int NewNode(int type = E_NUM) {
  int oldIndex = nodeIndex;
  nodes[oldIndex].type = type;
  nodeIndex++;
  return oldIndex;
}

int ParseOr(int& pos);

// a0&a1&a2 | b0&b1&b2 | c0&c1&c2 | ...
// a0&()&a2 | ()&b1&b2 | c0&c1&() | ...
inline int ParseParentheses(int& pos) {
  assert(str[pos] == '(');
  pos++;  // skip (
  int parenthesesIndex =  ParseOr(pos);
  assert(str[pos]== ')');
  pos++;  // skip )
  return parenthesesIndex;
}
inline int ParseNum(int& pos) {
  int numIndex = NewNode(E_NUM);
  nodes[numIndex].ans = str[pos] - '0';
  pos++;
  return numIndex;
}

// 0、1、()
inline int ParseBlock(int& pos) {
  if (str[pos] == '(') {
    return ParseParentheses(pos);
  } else {
    return ParseNum(pos);
  }
}

int ParseAnd(int& pos) {
  const int andIndex = NewNode(E_AND);
  nodes[andIndex].childs.push_back(ParseBlock(pos));
  while (str[pos] == '&') {
    pos++;
    nodes[andIndex].childs.push_back(ParseBlock(pos));
  }
  return andIndex;
}
int ParseOr(int& pos) {
  const int orIndex = NewNode(E_OR);
  nodes[orIndex].childs.push_back(ParseAnd(pos));
  while (str[pos] == '|') {
    pos++;
    nodes[orIndex].childs.push_back(ParseAnd(pos));
  }
  return orIndex;
}

int andSkipNum = 0, orSkipNum = 0;
int RunHead(int head) {
  Node& node = nodes[head];
  if (node.type == E_NUM) {
    return node.ans;
  }
  int ans = RunHead(node.childs[0]);
  const int childNum = node.childs.size();
  for (int i = 1; i < childNum; i++) {
    if (node.type == E_AND && ans == 0) {
      andSkipNum++;
    } else if (node.type == E_OR && ans == 1) {
      orSkipNum++;
    } else {
      ans = RunHead(node.childs[i]);
    }
  }
  node.ans = ans;
  return ans;
}
string space = "";
string TypeToString(int type) {
  if (type == E_NUM) {
    return "NUM";
  } else if (type == E_AND) {
    return "AND";
  } else {
    return "OR";
  }
}
void Dump(int head, int indent = 0) {
  Node& node = nodes[head];
  printf("%stype=%d[%s] ", space.substr(0, indent).c_str(), node.type, TypeToString(node.type).c_str());
  if (node.type == E_NUM) {
    printf(" val=%d\n", node.ans);
  } else {
    const int childNum = node.childs.size();
    printf(" childNum=%d ans=%d\n", childNum, node.ans);
    for (int i = 0; i < childNum; i++) {
      Dump(node.childs[i], indent + 2);
    }
  }
}

void Solver() {  //
  space.resize(100, ' ');
  scanf("%s", str);
  int pos = 0;
  int head = ParseOr(pos);
  printf("%d\n", RunHead(head));
  printf("%d %d\n", andSkipNum, orSkipNum);
//   Dump(head);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
01234567890123456789
0&(1|0)|(1|1|1&0)
*/