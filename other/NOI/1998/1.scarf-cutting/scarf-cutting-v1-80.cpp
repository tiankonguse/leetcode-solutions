/*
ID: tiankonguse
TASK: scarf-cutting
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "scarf-cutting"
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
// #define LOCAL_IO 0
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

void Solver() {  //
    int N, M;
    scanf("%d %d", &N, &M);

    // bad_up[r][j]: 第r行第j个△单元是否损坏（原始坐标Y=2j-1）
    // bad_dn[r][j]: 第r行第j个▽单元是否损坏（原始坐标Y=2j）
    vector<vector<int>> bad_up(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> bad_dn(N + 2, vector<int>(N + 2, 0));
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (y % 2 == 1) {
            bad_up[x][(y + 1) / 2] = 1;
        } else {
            bad_dn[x][y / 2] = 1;
        }
    }

    // 行内前缀和，用于快速查询某行某列范围内是否有损坏单元
    vector<vector<int>> preUp(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> preDn(N + 2, vector<int>(N + 2, 0));
    for (int r = 1; r <= N; r++) {
        for (int j = 1; j <= N; j++) {
            preUp[r][j] = preUp[r][j - 1] + bad_up[r][j];
            preDn[r][j] = preDn[r][j - 1] + bad_dn[r][j];
        }
    }

    // 查询第row行△列[l,r]是否有损坏
    auto queryUp = [&](int row, int l, int r) -> bool {
        if (l > r || r <= 0) return false;
        r = min(r, N);
        return (preUp[row][r] - preUp[row][l - 1]) > 0;
    };
    // 查询第row行▽列[l,r]是否有损坏
    auto queryDn = [&](int row, int l, int r) -> bool {
        if (l > r || r <= 0) return false;
        r = min(r, N);
        return (preDn[row][r] - preDn[row][l - 1]) > 0;
    };

    // maxK[r][j]: 以第r行第j个△为顶点的最大无损正三角形边长
    // 第r行有r个△，j从1到r
    vector<vector<int>> maxK(N + 2, vector<int>(N + 2, 0));
    for (int r = 1; r <= N; r++) {
        for (int j = 1; j <= r; j++) {
            if (bad_up[r][j]) continue;  // 顶点损坏
            maxK[r][j] = 1;
            for (int k = 2; r + k - 1 <= N; k++) {
                int bot = r + k - 1;
                // 检查底行新增单元：△列[j, j+k-1], ▽列[j, j+k-2]
                if (queryUp(bot, j, j + k - 1) || queryDn(bot, j, j + k - 2)) break;
                maxK[r][j] = k;
            }
        }
    }

    int ans = 0;

    // 枚举三种分割方向，对每种分割方向预处理前缀/后缀最大值
    // 两个△不重叠，必然可以被以下三种方向的直线分开：
    //   方向1：水平线（按行分）
    //   方向2：竖直线（按△列分）
    //   方向3：右斜线（按 j-r 值分）

    // ===== 方向1：水平线分割 =====
    // maxUp[cut]: 底行<=cut的最大三角形面积
    // maxDn[cut]: 顶行>=cut的最大三角形面积
    {
        vector<int> tmpU(N + 2, 0), tmpD(N + 2, 0);
        for (int r = 1; r <= N; r++) {
            for (int j = 1; j <= r; j++) {
                int k = maxK[r][j];
                if (k <= 0) continue;
                // 顶行r，所有边长1..k，底行r..r+k-1
                // 更新底行和顶行
                for (int kk = 1; kk <= k; kk++) {
                    tmpU[r + kk - 1] = max(tmpU[r + kk - 1], kk * kk);
                    tmpD[r] = max(tmpD[r], kk * kk);
                }
            }
        }
        vector<int> maxUp(N + 2, 0), maxDn(N + 2, 0);
        for (int r = 1; r <= N; r++) maxUp[r] = max(maxUp[r - 1], tmpU[r]);
        for (int r = N; r >= 1; r--) maxDn[r] = max(maxDn[r + 1], tmpD[r]);
        for (int cut = 0; cut <= N; cut++)
            if (maxUp[cut] > 0 && maxDn[cut + 1] > 0)
                ans = max(ans, maxUp[cut] + maxDn[cut + 1]);
    }

    // ===== 方向2：竖直线分割（按△列分） =====
    // 三角形顶点(r,j)边长k：最右△列=j+k-1，最左△列=j
    // maxLeft[cut]: 最右△列<=cut的最大三角形面积
    // maxRight[cut]: 最左△列>=cut的最大三角形面积
    {
        vector<int> tmpL(N + 2, 0), tmpR(N + 2, 0);
        for (int r = 1; r <= N; r++) {
            for (int j = 1; j <= r; j++) {
                int k = maxK[r][j];
                if (k <= 0) continue;
                for (int kk = 1; kk <= k; kk++) {
                    tmpL[j + kk - 1] = max(tmpL[j + kk - 1], kk * kk);
                    tmpR[j] = max(tmpR[j], kk * kk);
                }
            }
        }
        vector<int> maxLeft(N + 2, 0), maxRight(N + 2, 0);
        for (int c = 1; c <= N; c++) maxLeft[c] = max(maxLeft[c - 1], tmpL[c]);
        for (int c = N; c >= 1; c--) maxRight[c] = max(maxRight[c + 1], tmpR[c]);
        for (int cut = 0; cut <= N; cut++)
            if (maxLeft[cut] > 0 && maxRight[cut + 1] > 0)
                ans = max(ans, maxLeft[cut] + maxRight[cut + 1]);
    }

    // ===== 方向3：右斜线分割（按 j-r 值分） =====
    // 右斜坐标：右边界 d_max = j - r（不变），左下角 d_min = j - r - k + 1
    // 分割线左侧（d<=cut）：三角形最大右斜坐标 d_max <= cut，即 j-r <= cut
    // 分割线右侧（d>=cut+1）：三角形最小右斜坐标 d_min >= cut+1，即 j-r-k+1 >= cut+1
    {
        int offset = N;  // 偏移量，d范围[1-N,0]，加offset后[1,N]
        int sz = 2 * N + 2;
        vector<int> tmpSL(sz, 0), tmpSR(sz, 0);
        for (int r = 1; r <= N; r++) {
            for (int j = 1; j <= r; j++) {
                int k = maxK[r][j];
                if (k <= 0) continue;
                for (int kk = 1; kk <= k; kk++) {
                    int d_max = j - r;
                    int d_min = j - r - kk + 1;
                    tmpSL[d_max + offset] = max(tmpSL[d_max + offset], kk * kk);
                    tmpSR[d_min + offset] = max(tmpSR[d_min + offset], kk * kk);
                }
            }
        }
        vector<int> maxSL(sz, 0), maxSR(sz, 0);
        for (int d = -N; d <= N; d++)
            maxSL[d + offset] = (d == -N) ? tmpSL[d + offset] : max(maxSL[d - 1 + offset], tmpSL[d + offset]);
        for (int d = N; d >= -N; d--)
            maxSR[d + offset] = (d == N) ? tmpSR[d + offset] : max(tmpSR[d + offset], maxSR[d + 1 + offset]);
        for (int cut = -N; cut <= N - 1; cut++)
            if (maxSL[cut + offset] > 0 && maxSR[cut + 1 + offset] > 0)
                ans = max(ans, maxSL[cut + offset] + maxSR[cut + 1 + offset]);
    }

    printf("%d\n", ans);
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
  printf("my 用时: %.0lfms\n", costTime);
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
    printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      printf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
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
