/*
ID: tiankonguse
TASK: DetectiveReasoning
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1039
PATH:
submission:
*/
#define TASK "DetectiveReasoning"
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

enum StateType { GUILTY, NOT_GUILTY, DAY };
struct State {
  // 0: xxx(nameID) is  guilty
  // 1: xxx(nameID) is not guilty
  // 2: today is xxx(day)（星期几）
  int type;  //
  int xxx;
};

int m, n, p;
vector<string> names;
unordered_map<string, int> nameIds;
unordered_map<int, vector<State>> nameToWords;

vector<string> SplitWords(const string& s) {
  // split words by space
  vector<string> words;
  istringstream iss(s);
  string word;
  while (iss >> word) {
    words.push_back(word);
  }
  return words;
}

unordered_map<string, int> weeks = {{"Monday", 0}, {"Tuesday", 1},  {"Wednesday", 2}, {"Thursday", 3},
                                    {"Friday", 4}, {"Saturday", 5}, {"Sunday", 6}};

void Parse(string s) {
  if (s.empty()) return;
  while (!s.empty() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
  if (s.empty()) return;
  //   MyPrintf("s:[%d] [%s]\n", int(s.size()), s.c_str());
  if (s.back() != '.') return;
  s.pop_back();
  if (s.empty()) return;
  // s 格式： name: words
  // words 格式： xxx xxx xxx xxx.
  int pos = s.find(':');
  const string name = s.substr(0, pos);
  if (nameIds.count(name) == 0) return;
  const int nameID = nameIds[name];
  const string words = s.substr(pos + 2);
  if (words.empty()) return;
  vector<string> wordList = SplitWords(words);
  if (wordList.empty()) return;
  if (words == "I am guilty") {
    nameToWords[nameID].push_back({GUILTY, nameID});
  } else if (words == "I am not guilty") {
    nameToWords[nameID].push_back({NOT_GUILTY, nameID});
  } else if (wordList.back() == "guilty") {
    const string otherName = wordList[0];
    if (!nameIds.count(otherName)) return;
    const int otherNameID = nameIds[otherName];
    if (wordList.size() == 3 && wordList[1] == "is") {
      // XXX is guilty
      nameToWords[nameID].push_back({GUILTY, otherNameID});
      return;
    }
    if (wordList.size() == 4 && wordList[1] == "is" && wordList[2] == "not") {
      // XXX is not guilty
      nameToWords[nameID].push_back({NOT_GUILTY, otherNameID});
      return;
    }
  } else if (wordList.front() == "Today") {
    // Today is Xxxx
    const string day = wordList.back();
    if (!weeks.count(day)) return;
    if (wordList.size() == 3 && wordList[1] == "is") {
      nameToWords[nameID].push_back({DAY, weeks[day]});
    }
  }
}

const int bufsize = 4096;
char buffer[bufsize];

int CheckName(const int nameId, const int guiltyId, const int day) {
  int ans = 0;  // 1 真话, 2 假话, 0 可真可假， -1 矛盾
  for (const auto& state : nameToWords[nameId]) {
    const int xxx = state.xxx;
    if (state.type == GUILTY) {
      if (xxx == guiltyId) {
        ans |= 1;
      } else {
        ans |= 2;
      }
    } else if (state.type == NOT_GUILTY) {
      if (xxx == guiltyId) {
        ans |= 2;
      } else {
        ans |= 1;
      }
    } else if (state.type == DAY) {
      if (xxx == day) {
        ans |= 1;
      } else {
        ans |= 2;
      }
    }
  }
  if (ans == 3) {
    ans = -1;
  }
  return ans;
}
// 假设 nameId 是 guilty ，day 是 week，判断是否成立
bool Check(const int guiltyId, const int day) {
  int ans[3] = {0, 0, 0};
  for (int nameId = 1; nameId <= m; nameId++) {
    int ret = CheckName(nameId, guiltyId, day);
    if (ret == -1) return false;
    ans[ret]++;
  }
  return ans[2] <= n && n <= ans[0] + ans[2];
}

void Solver() {  //
  scanf("%d%d%d", &m, &n, &p);
  names.resize(m + 1);
  for (int i = 1; i <= m; i++) {
    scanf("%s", buffer);
    names[i] = buffer;
    nameIds[buffer] = i;
  }
  fgets(buffer, bufsize, stdin);  // skip \n
  while (p--) {
    fgets(buffer, bufsize, stdin);
    Parse(buffer);
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    for (int day = 0; day < 7; day++) {
      if (Check(i, day)) {
        if (ans == 0 || ans == i) {
          ans = i;
        } else {
          ans = -1;
          break;
        }
      }
    }
  }
  if (ans == 0) {
    printf("Impossible\n");
  } else if (ans != -1) {
    printf("%s\n", names[ans].c_str());
  } else {
    printf("Cannot Determine\n");
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