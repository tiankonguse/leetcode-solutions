/*
ID: tiankonguse
TASK: prefix
LANG: C++
*/
#define TASK "prefix"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int num = 0;
  int next[26];
};
Node nodes[max4];
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = false;
    node.num = 0;
    memset(node.next, -1, sizeof(node.next));
  }

  int Add() {
    int ret = index;
    Clear(ret);
    index++;
    return ret;
  }

 public:
  /** Initialize your data structure here. */
  Trie() { Init(); }

  void Init() {
    index = 0;
    Add();
  }

  /** Inserts a word into the trie. */
  void Insert(const string& word) {
    int root = 0;
    for (auto c : word) {
      int v = c - 'A';
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      nodes[root].num++;
      root = nodes[root].next[v];
    }
    nodes[root].num++;
    nodes[root].endFlag = 1;
  }

  /** Returns if the word is in the trie. */
  bool Search(const string& word, int root = 0, int index = 0) {
    int n = word.length();
    while (index < n) {
      char c = word[index];
      int v = c - 'A';
      int p = nodes[root].next[v];
      if (p == -1 && nodes[p].num > 0) return false;
      root = p;
      index++;
    }
    return nodes[root].endFlag == 1;
  }
};

char word[200];
const ll maxWord = 12;
const ll batchSize = 1000;
unordered_set<ll> h;
string buf;
string bufTmp;
vector<ll> dpPre;
vector<ll> dp;
ll ans = 0;
bool first = true;
ll offset = 0;

Trie trie;
void Search(const string& word, int root = 0, const int start = 0) {
  int index = start;
  int n = word.length();
  while (index < n) {
    char c = word[index];
    int v = c - 'A';
    int p = nodes[root].next[v];
    if (p == -1) return;
    if (nodes[p].endFlag) {
      dp[index + 1] = 1;
      ans = max(ans, offset + index + 1);
    }
    root = p;
    index++;
  }
}

void CalAns() {
  const ll n = buf.size();
  dp.clear();
  dp.resize(n + 1, 0);
  if (first) {
    dp[0] = 1;
    first = false;
  } else {
    for (int i = 0; i < dpPre.size(); i++) {
      dp[i] = dpPre[i];
    }
  }

  for (ll i = 0; i < n; i++) {
    if (dp[i] == 0) continue;  // 不可到达
    Search(buf, 0, i);
  }

  // 保留最后 maxWord 个字符 ,不够时，代表计算完了
  if (n <= maxWord) {
    return;
  }

  bufTmp.clear();
  dpPre.resize(maxWord + 1, 0);
  for (int i = 0; i < maxWord; i++) {
    dpPre[i] = dp[n - maxWord + i];
    bufTmp.push_back(buf[n - maxWord + i]);
  }
  bufTmp[maxWord] = bufTmp[n];  // 有可能完全匹配，指向 maxWord
  buf.swap(bufTmp);
  offset += n - maxWord;
}

void Add(const char* s) {
  buf.append(s);
  if (buf.size() < batchSize) {
    return;
  }
  CalAns();
}

void Solver() {  //
  trie.Init();
  while (true) {
    scanf("%s", word);
    if (word[0] == '.') {
      break;
    }
    trie.Insert(word);
  }

  while (scanf("%s", word) != EOF) {
    if (word[0] == '.') break;
    Add(word);
  }
  CalAns();
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*



*/