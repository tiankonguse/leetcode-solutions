/*
分块算法

对区间划分为 `sqrt(N)` 个相等的子区间，则每个区间大小为 `sqrt(N)`。  
关键优化：如果对一个完整的子区间进行操作，则使用延迟标记来 `O(1)`处理。  


基于关键优化，来看下区间操作的复杂度。  
一个区间的左端点可能没有覆盖完整的子区间，所以需要暴力扫描对应的子区间，最多循环`sqrt(N)`次。  
对于中间的部分，都是完整覆盖子区间，所以使用延迟标记即可，最多 `sqrt(N)`个。  
对于右端点，同样可能没有完整的覆盖子区间，也需要暴力扫描对应的子区间，最多循环`sqrt(N)`次。  
综合，一次区间操作最多循环 `3 * sqrt(N)`次。  


查询操作与区间操作完全一样，也是最多循环 `3*sqrt(N)`次。  


故每次操作平均都需要 `sqrt(N)` 的复杂度，`q` 次操作，复杂度就是 `q * sqrt(N)`。  
*/


typedef long long ll;
struct Block {
  Block() {
    cnt.clear();
    lazy = 0;
  }
  unordered_map<ll, int> cnt;
  ll lazy = 0;
};
struct SqrtBlock {
  vector<int> nums;
  vector<Block> blocks;
  int blockSize;
  int blockCnt;
  void Init(const vector<int>& nums) {
    int n = nums.size();
    this->nums = nums;
    blockSize = max(1, (int)sqrt(n));
    blockCnt = (n + blockSize - 1) / blockSize;
    blocks.clear();
    blocks.resize(blockCnt);
    for (int i = 0; i < n; i++) {
      int b = i / blockSize;
      blocks[b].cnt[nums[i]]++;
    }
  }
  void Update(const int l, const int r, const ll val) {
    int startBlock = l / blockSize;
    int endBlock = r / blockSize;
    if (startBlock == endBlock) {
      for (int i = l; i <= r; i++) {
        blocks[startBlock].cnt[nums[i]]--;
        nums[i] += val;
        blocks[startBlock].cnt[nums[i]]++;
      }
    } else {
      {  // 左半部
        int L = l;
        int R = (startBlock + 1) * blockSize - 1;
        for (int i = L; i <= R; i++) {
          blocks[startBlock].cnt[nums[i]]--;
          nums[i] += val;
          blocks[startBlock].cnt[nums[i]]++;
        }
      }
      {  // 中间
        for (int b = startBlock + 1; b < endBlock; b++) {
          blocks[b].lazy += val;
        }
      }
      {  // 右半部
        int L = endBlock * blockSize;
        int R = r;
        for (int i = L; i <= R; i++) {
          blocks[endBlock].cnt[nums[i]]--;
          nums[i] += val;
          blocks[endBlock].cnt[nums[i]]++;
        }
      }
    }
  }
  ll Query(const int l, const int r, const ll tot) {
    ll ret = 0;

    int startBlock = l / blockSize;
    int endBlock = r / blockSize;
    if (startBlock == endBlock) {
      for (int i = l; i <= r; i++) {
        if (nums[i] + blocks[startBlock].lazy == tot) {
          ret++;
        }
      }
    } else {
      {  // 左半部
        int L = l;
        int R = (startBlock + 1) * blockSize - 1;
        for (int i = L; i <= R; i++) {
          if (nums[i] + blocks[startBlock].lazy == tot) {
            ret++;
          }
        }
      }
      {  // 中间
        for (int b = startBlock + 1; b < endBlock; b++) {
          ll realTarget = tot - blocks[b].lazy;
          if (blocks[b].cnt.count(realTarget)) {
            ret += blocks[b].cnt[realTarget];
          }
        }
      }
      {  // 右半部
        int L = endBlock * blockSize;
        int R = r;
        for (int i = L; i <= R; i++) {
          if (nums[i] + blocks[endBlock].lazy == tot) {
            ret++;
          }
        }
      }
    }

    return ret;
  }
};