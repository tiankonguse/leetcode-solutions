// 输入顶点个数和边，输出欧拉路径 或 欧拉回路

/* this is exactly the Eulerian Path algorithm */
// nconn 节点个数, conn 邻接矩阵，允许重边, deg 顶点度数, path 逆序答案
void find_path(int loc) {
  for (int lv = 0; lv < nconn; lv++)
    if (conn[loc][lv]) {
      /* delete edge */
      conn[loc][lv]--;
      conn[lv][loc]--;
      deg[lv]--;
      deg[loc]--;

      /* find path from new location */
      find_path(lv);
    }

  /* add this node to the `end' of the path */
  path[plen++] = loc;
}

class Solution {
 public:
  vector<int> edges;
  vector<vector<pair<int, int>>> g;
  int n, m;

  vector<int> vals;
  vector<int> nexts;
  vector<int> pres;
  int index = 0;
  int maxN = 0;

  int Add(int s) {
    int oldIndex = index;
    index++;
    vals[oldIndex] = s;
    return oldIndex;
  }

  void Bind(int a, int b) {
    nexts[a] = b;
    pres[b] = a;
  }

  int NextBack(int u) {
    while (g[u].size() > 0) {
      auto [v, i] = g[u].back();
      if (edges[i] == 0) {
        edges[i] = 1;
        g[u].pop_back();
        return v;
      } else {
        g[u].pop_back();
      }
    }
    return -1;
  }
  bool IsEmptyNode(int u) {
    while (g[u].size() > 0) {
      auto [v, i] = g[u].back();
      if (edges[i] == 0) {
        return false;
      } else {
        g[u].pop_back();
      }
    }
    return true;
  }

  // first -> second
  int Traver(int first) {
    while (g[vals[first]].size() > 0) {
      int c = NextBack(vals[first]);
      if (c == -1) break;
      const int second = Add(c);
      Bind(first, second);
      first = second;
    }
    return first;
  }

  int FindFirstNode() {
    int firstNoEmptyNode = 0;
    for (int i = 1; i <= maxN; i++) {
      if (g[i].size() == 0) continue;
      if (firstNoEmptyNode == 0) firstNoEmptyNode = i;
      if (g[i].size() % 2 == 1) {
        return i;
      }
    }
    return firstNoEmptyNode;  // 如果没有奇数度数，则使用第一个最小节点当做出发位置
  }
  vector<int> ans;

 public:
  const vector<int>& findItinerary(const int n,
                                   const vector<pair<int, int>>& tickets) {  //
    m = tickets.size();
    g.resize(n + 1);
    edges.resize(m + 1, 0);
    for (int i = 0; i < m; i++) {
      auto [a, b] = tickets[i];
      g[a].push_back({b, i});
      g[b].push_back({a, i});
      maxN = max(maxN, max(a, b));
    }
    for (int i = 1; i <= maxN; i++) {
      sort(g[i].begin(), g[i].end(), [](auto a, auto b) { return a > b; });
    }

    vals.resize(m + 10, -1);
    nexts.resize(m + 10, -1);
    pres.resize(m + 10, -1);

    int s = FindFirstNode();
    const int first = Add(s);
    const int last = Traver(first);
    while (index <= m) {
      // 从最后一个向前找到最后一个非空节点
      int mid = last;
      while (mid != -1 && vals[mid] != -1 && IsEmptyNode(vals[mid])) {
        mid = pres[mid];
      }
      // mid -> first
      int val = NextBack(vals[mid]);
      const int midFirst = Add(val);  // 首个节点
      int midLast = Traver(midFirst);
      // first-> ... -> mid -> ... last
      // mid : midFirst -> ... -> midLast
      const int nextMid = nexts[mid];
      Bind(midLast, nextMid);
      Bind(mid, midFirst);
    }

    ans.reserve(m + 1);
    int it = first;
    while (it != -1 && vals[it] != -1) {
      ans.push_back(vals[it]);
      it = nexts[it];
    }
    return ans;
  }
};