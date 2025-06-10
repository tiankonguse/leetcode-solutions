/*
ID: tiankonguse
TASK: arena
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/record/220035641
PATH: P11234 [CSP-S 2024] 擂台游戏
submission: 询问去重
*/
#define TASK "arena"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)               \
  do {                              \
    if (debug) assert(__VA_ARGS__); \
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

void InitIO() {
//
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

const int N = 1e5 + 10;
int n, m;
int K;                  // 2^K >= n，K 为最小的满足条件的值
ll AA[N];               // 下标从1开始, {能力，编号}
pair<ll, ll> A[4 * N];  // 下标从1开始
int flag[4 * N];        // 下标从1开始
ll C[N];                // 下标从1开始
ll CC[N];
ll VV[N];
int mm;
unordered_map<ll, ll> H;
ll X[4];
char str[N];
int dataOffset = 0;

int UpPow(int x) {
  int res = 0;
  while ((1 << res) < x) {
    res++;
  }
  return res;
}

void Input() {
  scanf("%d%d", &n, &m);
  K = UpPow(n);
  dataOffset = 1 << K;
  MyPrintf("K=%d 1<<K=%d\n", K, dataOffset);
  for (int j = dataOffset, i = 1; j < 2 * dataOffset; j++, i++) {
    A[j] = {0, i};  // 默认全部设置为0
  }
  for (int i = 1, j = dataOffset; i <= n; i++, j++) {
    scanf("%lld", &AA[i]);
    A[j] = {AA[i], i};
  }
  //   MyPrintf("\n", K);
  for (int i = 1; i <= m; i++) {
    scanf("%lld", &C[i]);
    H[C[i]] = 0;
  }
  mm = 0;
  for (auto& [k, v] : H) {
    CC[mm] = k;
    v = mm;
    mm++;
  }
  for (int i = 1; i <= m; i++) {
    C[i] = H[C[i]];
  }
  for (int k = K - 1, offset = dataOffset; k >= 0; k--) {
    scanf("%s", str);
    const int step = 1 << k;
    offset -= step;
    // MyPrintf(" step=%d offset=%d\n", k, step, offset);
    for (int j = 0; j < step; j++) {
      flag[offset + j] = str[j] - '0';  // 将字符转换为数字
    }
  }

  // for (int k = 0; k <= K; k++) {
  //   MyPrintf("%d cnt=[%d]:", k, (1 << k));
  //   for (int i = 0; i < (1 << k); i++) {
  //     MyPrintf("%d=%d ", (1 << k) + i, flag[(1 << k) + i]);
  //   }
  //   MyPrintf("\n");
  // }
}
void Reinit() {
  // O(n) 计算输入数据
  for (int i = 1, j = dataOffset; i <= n; i++, j++) {
    A[j] = {AA[i] ^ X[i % 4], i};
    // MyPrintf("A[%d]=%lld\n", i, A[j].first);
  }
  // O(n) 计算已确定答案的数据
  for (int k = K - 1, offset = dataOffset; k >= 0; k--) {
    const int step = 1 << k;
    const int R = K - k;  // 比赛轮数，是逆序的，从编号 1 开始
    offset -= step;
    for (int j = 0; j < step; j++) {
      const int no = offset + j;
      const int v = flag[no];
      if (A[no * 2 + v].first >= R) {
        A[no] = A[no * 2 + v];
      } else {
        A[no] = A[no * 2 + (v ^ 1)];
      }
    }
  }
}

ll sum = 0;
ll RangeSum1(ll l, ll r) {  // 计算 [l, r] 的和
  MyPrintf("add range[%lld,%lld]\n", l, r);
  return (r - l + 1) * (l + r) / 2;
}
ll RangeSum(ll l, ll r) {
  if (l > r) return 0;
  ll n = r - l + 1;
  ll mid = l + r;
  if (n % 2 == 0) {
    return n / 2 * mid;
  } else {
    return mid * n / 2 + mid / 2;
  }
}
/*
     [leftOffset,rightOffset]: 这个比赛树下，叶子节点的去加盟
    p: 当前处理的树根节点
    queryOffset: 查询前 queryOffset 个人的比赛情况，固定值，永远不变
    k: 当前处于第几层，从0开始，K-1 是最底层
    R: 当前比赛的轮数，是逆序的，越往下越小
    minVal: 当前子树要获胜整个比赛，需要的最小能量值
    return <minVal, otherRange>
    minVal 子树胜出的最小能量值，肯定存在
    otherRange 子树胜出的区间能量值 [otherRange, -1]，有空闲时可能存在。 -1 代表不存在
*/
int queryOffset = 0;
pair<int, int> Dfs(const int p, const int R, const int minVal) {
  MyAssert(R >= 0);
  const int all = 1 << R;
  const int half = all >> 1;
  const int leftOffset = p << R;
  const int rightOffset = leftOffset + all - 1;
  const int leftNo = leftOffset - dataOffset + 1;
  const int rightNo = leftNo + all - 1;
  const int v = flag[p];  // 抽签，左树还是右树
  MyPrintf("p=%d  R=%d minVal=%d offset=[%d,%d] flag[p]=%d\n", p, R, minVal, leftOffset, rightOffset, flag[p]);
  // 节点 p 下面进行 R 轮，涉及 all 个人， 范围是 [leftOffset, rightOffset], queryOffset 之后的都是空闲节点
  if (p >= dataOffset) {
    MyAssert(R == 0);  // 此时 R 必须是 0
    MyAssert(leftNo == A[p].second);
    if (p <= queryOffset) {
      if (A[p].first >= minVal) {  // 可以获胜整个比赛
        sum += A[p].second;
      }
      return {A[p].first, -1};  // 最小获胜值是 A[p].first，-1 代表没有右区间，只有一个答案
    } else {
      sum += leftNo;  // 空闲节点，可以选择无限大从而获胜
      return {0, 0};  // [0,inf] 都是答案，最小值是 0
    }
  }
  MyAssert(R > 0);  // 此时 R 必须大于0

  if (queryOffset >= rightOffset) {  // 所有队员都是确定的，答案是确定的
    if (A[p].first >= minVal) {      // 可以获胜整个比赛
      sum += A[p].second;
      MyPrintf("add p=%d  R=%d minVal=%d leftOffset=%d  %lld\n", p, R, minVal, leftOffset, A[p].second);
    }
    return {A[p].first, -1};  // 最小获胜值是 A[p].first，-1 代表没有右区间，只有一个答案
  }
  if (queryOffset < leftOffset) {  // 所有队员都是空的，任意位置都可以胜出， 且胜出的能量值可以是所有大于等于0的值
    sum += RangeSum(leftNo, rightNo);
    return {0, 0};
  }
  // 根据抽签结果 与 左子树是否是确定的，分4种情况
  MyPrintf("leftOffset=%d half=%d pk=%d\n", leftOffset, half, int(queryOffset >= leftOffset + half - 1));
  const int midOffset = leftOffset + half - 1;  // [leftOffset, midOffset] [midOffset+1, rightOffset]
  if (queryOffset >= midOffset) {               // 左子树是确定的
    if (v == 0) {                               // 左子树决策
      auto [leftMinWinVal, leftRangeWinVal] = Dfs(p * 2, R - 1, max(minVal, R));
      MyAssert(leftRangeWinVal == -1);
      if (leftMinWinVal < R) {  // 左子树必输
        return Dfs(p * 2 + 1, R - 1, minVal);
      } else {  // 左子树必赢，不需要看右子树了
        return {leftMinWinVal, leftRangeWinVal};
      }
    } else {  // 由右子树决策
      auto [rightMinWinVal, rightRangeWinVal] = Dfs(p * 2 + 1, R - 1, max(minVal, R));
      if (rightMinWinVal < R) {  // 右子树可以输比赛
        auto [leftMinWinVal, leftRangeWinVal] = Dfs(p * 2, R - 1, minVal);
        MyAssert(leftRangeWinVal == -1);
        if (rightRangeWinVal == -1) {  // 右子树输掉比赛
          return {leftMinWinVal, leftRangeWinVal};
        }
        // 右子树可能是 <R-a, R+b> ， 此时右子树胜出时的最小值是 R+b
        return {min(leftMinWinVal, max(R, rightRangeWinVal)), rightRangeWinVal};
      } else {
        return {rightMinWinVal, rightRangeWinVal};
      }
    }
  } else {         // 右半部全部是空的
    if (v == 1) {  // 由右树确定答案
      // 右子树的所有编号全部是答案，构造答案：对应的编号无限大，其他都是0，则这个编号必然获胜
      // auto [rightMinWinVal, rightRangeWinVal] = Dfs(p * 2 + 1, R - 1, max(minVal, R));
      // MyAssert(rightMinWinVal == 0);
      // MyAssert(rightRangeWinVal == 0);
      sum += RangeSum(leftNo + half, leftNo + all - 1);
      // 右子树想要获胜，能力值必须大于当前轮数 R，故能力值范围是 [R, INF]
      int rightRangeWinVal = R;

      // 右子树选择小于等于 R 的值，把胜利权利转让给左子树, 此时子树的能力不需要大于当前轮数
      auto [leftMinWinVal, leftRangeWinVal] = Dfs(p * 2, R - 1, minVal);
      if (leftRangeWinVal != -1) {
        rightRangeWinVal = min(rightRangeWinVal, leftRangeWinVal);
      }
      return {min(leftMinWinVal, R), rightRangeWinVal};
    } else {  // 左半部来确定答案
      // 答案由左子树确定，左子树要获胜，需要大于当前轮数，还需要大于后续的比赛轮数 minVal
      auto [leftMinWinVal, leftRangeWinVal] = Dfs(p * 2, R - 1, max(minVal, R));
      if (leftMinWinVal < R) {  // 左子树可以输掉比赛
        // 右子树全部是答案, 构造答案：对应的编号无限大，其他都是0，则这个编号必然获胜
        // auto [rightMinWinVal, rightRangeWinVal] = Dfs(p * 2 + 1, R - 1, max(minVal, R));
        // MyAssert(rightMinWinVal == 0);
        // MyAssert(rightRangeWinVal == 0);
        sum += RangeSum(leftNo + half, leftNo + all - 1);
        return {0, 0};
      } else {
        return {leftMinWinVal, leftRangeWinVal};
      }
    }
  }
}
ll Query(int c) {
  const int CK = UpPow(c);
  const int leftOffset = dataOffset;
  const int rightOffset = dataOffset + (1 << CK) - 1;
  queryOffset = dataOffset + c - 1;
  sum = 0;
  int R = CK;  // 比赛轮数，是逆序的，从编号 1 开始
  int p = 1 << (K - CK);
  // while (R > CK) {
  //   p = p * 2;
  //   R--;
  // }
  MyPrintf("leftOffset=%d rightOffset=%d queryOffset=%d p=%d R=%d \n", leftOffset, rightOffset, queryOffset, p, R);
  auto [leftMinWinVal, leftRangeWinVal] = Dfs(p, R, 0);
  MyPrintf("Query: leftMinWinVal=%d leftRangeWinVal=%d\n", leftMinWinVal, leftRangeWinVal);
  return sum;
}

void Solver() {  //
  Input();

  int t;
  scanf("%d", &t);
  while (t--) {
    for (int i = 0; i < 4; i++) {
      scanf("%lld", &X[i]);
    }
    Reinit();
    ll ans = 0;
    for (int i = 0; i < mm; i++) {
      VV[i] = Query(CC[i]);
    }
    for (int i = 1; i <= m; i++) {
      ll c = VV[C[i]];
      MyPrintf("C[%d]=%lld ret=%lld\n", i, C[i], c);
      ans ^= c * i;
    }
    printf("%lld\n", ans);
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  MyPrintf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/