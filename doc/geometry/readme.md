# 几何



## 求两点的直线

```cpp
// 第零步，标准化向量，方向朝右或者上
if (x1 > x2 || (x1 == x2 && y1 > y2)) {
  swap(x1, x2);
  swap(y1, y2);
}
// 第一步，计算出向量
const ll dx = x2 - x1, dy = y2 - y1;
// 第二步：计算出向量的长度的平方
const ll len2 = dx * dx + dy * dy;
// 第三步：规范化向量，来代表斜率
const ll g = Gcd(abs(dx), abs(dy));
const ll nx = dx / g, ny = dy / g;
// 第四步：直线使用 ax + by + c = 0 来表示，其中 a,b,c 为整数，且 a,b 互质
const ll a = ny, b = -nx, c = nx * y1 - ny * x1;
```