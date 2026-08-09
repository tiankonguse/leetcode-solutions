/*
ID: tiankonguse
TASK: Cryptarithm
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1092
PATH:
submission:
*/
#define TASK "Cryptarithm"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 0;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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

void InitIO(int fileIndex) {  //
// #define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

int n;
char s1[30], s2[30], s3[30];
int charToVal[30];
char valToChar[30];

int firstCharVal = -1;
vector<int> firstValList;
int secondCharVal = -1;
vector<int> secondValList;

bool CheckMatchEx(const int val, const int c) {
  if (charToVal[c] == val) return true;
  if (val < 0 || val > n) return false;
  if (valToChar[val] != 0 && valToChar[val] != c) return false;
  return true;
}
bool CheckMatch(const int val, const int c) {
  if (charToVal[c] == val) return true;
  if (val < 0 || val > n) return false;
  // 非0时分两种情况，可以借位与不借位
  return CheckMatchEx(val, c) || CheckMatchEx(val - 1, c);
}

bool CheckSubtractionOK(int v3, int v2, int c1) {
  const int val1 = v3 - v2;      // 不借位
  const int val2 = v3 + n - v2;  // 借位
  return CheckMatch(val1, c1) || CheckMatch(val2, c1);
}
void SetSubtraction(int v3, int v2, int c1) {
  const int val1 = v3 - v2;      // 不借位
  const int val2 = v3 + n - v2;  // 借位

  secondCharVal = c1;
  if (val1 >= 0 && val1 <= n && valToChar[val1] == 0) {
    secondValList.push_back(val1);
  }
  if (val1 > 0 && val1 <= n && valToChar[val1 - 1] == 0) {
    secondValList.push_back(val1 - 1);
  }
  if (val2 >= 0 && val2 <= n && valToChar[val2] == 0) {
    secondValList.push_back(val2);
  }
  if (val2 > 0 && val2 <= n && valToChar[val2 - 1] == 0) {
    secondValList.push_back(val2 - 1);
  }
}
// 不考虑进位，看高位是否冲突
bool CheckNoConflict() {
  int carry = 0;
  int full = 1;

  firstCharVal = -1;
  firstValList.clear();
  secondCharVal = -1;
  secondValList.clear();

  for (int i = n - 1; i >= 0; i--) {
    const int c1 = s1[i] - 'A';
    const int c2 = s2[i] - 'A';
    const int c3 = s3[i] - 'A';
    const int v1 = charToVal[c1];
    const int v2 = charToVal[c2];
    const int v3 = charToVal[c3];

    if (full == 1 && v1 != -1 && v2 != -1 && v3 != -1) {
      const int sum = v1 + v2 + carry;
      const int val3 = sum % n;
      const int carry3 = sum / n;
      if (val3 != v3) return false;
      carry = carry3;
      continue;
    }
    full = 0;
    carry = 0;

    // case1: 进位与不进位都不行
    if (v1 != -1 && v2 != -1 && v3 != -1) {
      if ((v1 + v2) % n != v3 && (v1 + v2 + 1) % n != v3) return false;
    }

    // case2: 最高位，不能进位
    if (i == 0 && v1 != -1 && v2 != -1) {
      if (v1 + v2 >= n) return false;
    }
    // case3: v3 没有赋值，推导出来的值冲突
    if (v1 != -1 && v2 != -1 && v3 == -1) {
      const int val1 = (v1 + v2) % n;
      const int val2 = (v1 + v2 + 1) % n;  // 有进位
      if (valToChar[val1] != 0 && valToChar[val2] != 0) return false;
      if (firstCharVal == -1) {
        firstCharVal = c3;
        if (valToChar[val1] == 0) firstValList.push_back(val1);
        if (valToChar[val2] == 0) firstValList.push_back(val2);
      }
    }

    // case4: V1 没有赋值，判断是否有冲突
    if (v1 == -1 && v2 != -1 && v3 != -1) {
      if (!CheckSubtractionOK(v3, v2, c1)) {
        return false;
      }
      // if (secondCharVal == -1) {
      //   SetSubtraction(v3, v2, c1);
      // }
    }
    // case5: V2 没有赋值，判断是否有冲突
    if (v1 != -1 && v2 == -1 && v3 != -1) {
      if (!CheckSubtractionOK(v3, v1, c2)) {
        return false;
      }
      // if (secondCharVal == -1) {
      //   SetSubtraction(v3, v1, c2);
      // }
    }
  }
  if (full == 1 && carry != 0) return false;
  return true;
}

vector<int> cnt;
vector<pair<int, int>> orderChar;
vector<int> valList;
int valNum;
bool Dfs(const int p) {
  if (!CheckNoConflict()) {
    return false;
  }
  if (p == n) {
    return true;
  }
  if (firstCharVal != -1 && charToVal[firstCharVal] == -1) {  // 存在字符只有两个选择，优先选择
    int backChar = firstCharVal;
    auto backValList = firstValList;
    for (auto val : backValList) {
      // 有可能这个 val 已经其他贪心策略使用了
      if (valToChar[val] != 0) continue;
      charToVal[backChar] = val;
      valToChar[val] = backChar + 'A';
      // 由于使用贪心策略，p 位置不变
      if (Dfs(p)) return true;
      charToVal[backChar] = -1;
      valToChar[val] = 0;
    }
  }
  const int c = orderChar[p].second;
  if (charToVal[c] != -1) {
    return Dfs(p + 1);
  }

  for (int i = 0; i < valNum; i++) {
    const int val = valList[i];
    // 有可能这个 val 已经其他贪心策略使用了
    if (valToChar[val] != 0) continue;

    swap(valList[i], valList[valNum - 1]);
    valNum--;

    charToVal[c] = val;
    valToChar[val] = c + 'A';
    if (Dfs(p + 1)) {
      return true;
    }
    charToVal[c] = -1;
    valToChar[val] = 0;

    valNum++;
    swap(valList[i], valList[valNum - 1]);
  }
  return false;
}

void Solver() {  //
  scanf("%d", &n);
  scanf("%s%s%s", s1, s2, s3);
  memset(charToVal, -1, sizeof(charToVal));
  memset(valToChar, 0, sizeof(valToChar));
  cnt.resize(n, 0);
  for (int i = 0; i < n; i++) {
    cnt[s1[i] - 'A']++;
    cnt[s2[i] - 'A']++;
    cnt[s3[i] - 'A']++;
  }

  valList.resize(n);
  orderChar.reserve(n);
  for (int i = 0; i < n; i++) {
    valList[i] = i;
    orderChar.push_back(make_pair(cnt[i], i));
  }
  valNum = n;
  // 逆序排序
  sort(orderChar.begin(), orderChar.end(), greater<pair<int, int>>());

  Dfs(0);
  for (int i = 0; i < n; i++) {
    printf("%d%c", charToVal[i], i == n - 1 ? '\n' : ' ');
  }
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  MyPrintf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    MyPrintf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      MyPrintf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      MyPrintf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}
