#include <bits/stdc++.h>
using namespace std;
int a[100002];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {  // 输入n个数字
    cin >> a[i];
  }
  priority_queue<int> p;                             // 大根堆（存放较小的元素）
  priority_queue<int, vector<int>, greater<int>> q;  // 小根堆（存放较大的元素）

  for (int i = 0; i < n; i++) {
    // 1. 插入元素
    if (p.empty() || a[i] <= p.top()) {
      p.push(a[i]);  // 插入大根堆
    } else {
      q.push(a[i]);
    }

    // 2. 平衡堆
    if (p.size() > 1 + q.size()) {
      q.push(p.top());  // 先插入
      p.pop();          // 后删除
    } else if (q.size() > 1 + p.size()) {
      p.push(q.top());
      q.pop();
    }

    // 3. 分奇偶数打印
    double ans = 0.0;
    int total = p.size() + q.size();                  // 当前两个堆的总数
    if (total % 2 == 1) {                             // 奇数
      ans = p.size() > q.size() ? p.top() : q.top();  // 取元素个数多的堆的堆顶
    } else {
      ans = (p.top() + q.top()) * 1.0 / 2;
    }
    cout << ans << endl;
  }
  return 0;
}