// 枚举子集
// 复杂度：假设有 k 个 1，复杂度为 O(2^k)
for (int sub = mask; sub; sub = (sub - 1) & mask) {
  ll oneCount = __builtin_popcount(sub);
}

// 子集容斥
// 根据子集 1 的个数，奇数加，偶数减
for (int sub = mask; sub; sub = (sub - 1) & mask) {
  ll oneCount = __builtin_popcount(sub);
  if (oneCount % 2 == 1) {
    ans = (ans + SolverSub(sub)) % mod;
  } else {
    ans = (ans - SolverSub(sub) + mod) % mod;
  }
}


// 求 mask
ll kMaxBit = 1;  // 10^6
while ((1 << kMaxBit) <= maxVal) {
  kMaxBit++;
}

// 子集最大值
// dp[mask] 含义：mask 所有子集的最大值
// 复杂度：O(2^k)
// 拆分为 maxBit 个子问题
const int MaxBitVal = 1 << maxBit;
for (auto v : nums) {
  dp[v] = v;
}
for (int i = 0; i < MaxBitVal; i++) {
  for (int j = 0; j < maxBit; j++) {
    dp[i | (1 << j)] = max(dp[i | (1 << j)], dp[i]);
  }
}


for (int i = 0; i < MaxBitVal; i++) {
  for (int j = 0; j < maxBit; j++) {
    if (i & (1 << j)){
      dp[i] = max(dp[i ^ (1 << j)], dp[i]);
    }
  }
}


// 子集和
// dp[mask] 含义：mask 所有子集的和
// 复杂度：O(2^k)
// 将子集拆分为若干没有重合的子集
vector<vector<ll>> preMaskCount(kMaxBit + 1, vector<ll>(kMaxMask, 0));
for (ll x : nums) {
  preMaskCount[0][x]++;
}
for (int i = 0; i < kMaxBit; i++) {
  for (int mask = 0; mask < kMaxMask; mask++) {
    preMaskCount[i + 1][mask] = preMaskCount[i][mask];
    if (mask & (1 << i)) {
      preMaskCount[i + 1][mask] += preMaskCount[i][mask ^ (1 << i)];
    }
  }
}