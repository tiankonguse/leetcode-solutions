# DP 模版


## 状态压缩


枚举 mask 的所有子集


```cpp
for (int sub = mask; sub; sub = (sub - 1) & mask) {
  
}
```

## 倍增

见 [LCA](../lca.cpp)