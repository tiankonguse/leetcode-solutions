#include <bits/stdc++.h>
#include <stdarg.h>
#include <time.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

// template <class T>
// using min_queue = priority_queue<T, vector<T>, greater<T> >;

// template <class T>
// using max_queue = priority_queue<T>;

const double base_eps = 1e-7;
// const int INF = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
// const int max3 = 4100, max4 = 11100, max5 = 200100, max6 = 2000100;
// const int inf = 0x3f3f3f3f;
// typedef unsigned uint;
// typedef unsigned char uchar;
const int null = -1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

// dir : up, down, right, right
// int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

// dir : up, right, down, right
// int dir[4][2] = {{0,1}},{1,0},{0,-1,{-1,0}};

// 求数组和
// int sum = accumulate(stones.begin(),stones.end(),0)/2;

// 多重set（删除是全删）
// multiset<int> s;

// c++11 遍历容器
//  for(auto stone : stones)

// vecToTree({});
// ListNode* root = vecToList({1,2,3,4});

// 反转字符串
// std::reverse(a.begin(),a.end());

// 优先队列(堆)
// typedef struct {
//    int a,b;
//} Node;
// struct cmp {
//    bool operator()(const Node &t1,const Node &t2) {
//        return t1.b<t2.b;
//    }
//};
// priority_queue<Node,vector<Node>, cmp> Q;
// priority_queue<int, vector<int>, greater<int>>
// priority_queue<int, vector<int>, less<<int>>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x = 0) : val(x), next(NULL) {}
};

struct DoublyListNode {
  int val;
  DoublyListNode *next, *prev;
  DoublyListNode(int x) : val(x), next(NULL), prev(NULL) {}
};

ListNode* vecToList(vector<int> data, ListNode* root) {
  int index = 0;
  ListNode* pre = NULL;
  for (auto it = data.begin(); it != data.end(); it++) {
    int val = *it;
    ListNode* now = root + index++;

    now->val = val;
    now->next = NULL;
    if (pre == NULL) {
      pre = now;
    } else {
      pre->next = now;
      pre = now;
    }
  }
  return root;
}

ListNode* vecToList(vector<int> data) {
  ListNode* root = NULL;
  ListNode* pre = NULL;
  for (auto it = data.begin(); it != data.end(); it++) {
    ListNode* now = new ListNode(*it);
    if (pre == NULL) {
      root = pre = now;
    } else {
      pre->next = now;
      pre = now;
    }
  }
  return root;
}

void output(ListNode* root) {
  set<ListNode*> s;
  while (root != nullptr) {
    if (s.find(root) != s.end()) {
      printf("[%d]", root->val);
      break;
    }
    s.insert(root);
    printf("%d ", root->val);
    root = root->next;
  }
}

/**
 * Definition for a binary tree node.
 */

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x = 0) : val(x), left(NULL), right(NULL) {}
};

enum {
  NODE_LEFT = 0,
  NODE_RIGHT = 1,
  NODE_ROOT = -1,
};

// struct Node {
//    int index;
//    int val;
//    int pre;
//    int type; // 0 left, 1 right , -1 root
//    Node(int index=-1, int val = -1, int pre = -1, int type =
//    -1):index(index), val(val), pre(pre), type(type) {
//
//    }
//};

/*
 *  TreeNode list[100];
 *  vector<Node> data;
 *
 *      0
 *     / \
 *    1   2
 *  data = {
 *      {0, 0, -1, NODE_ROOT},
 *      {1, 1, 0, NODE_LEFT},
 *      {2, 2, 0, NODE_RIGHT},
 *  };
 *  memset(list, 0, sizeof(list));
 *  born(data, list);
 *
 */
// void born(vector<Node>&data, TreeNode* root) {
//    for(vector<Node>::iterator it = data.begin(); it != data.end(); it++) {
//        int index = it->index;
//        int val = it->val;
//        int pre = it->pre;
//        int type = it->type;
//
//        root[index].val = val;
//        if(pre != -1) {
//            if(type == 0) {
//                root[pre].left = root + index;
//            } else if(type == 1) {
//                root[pre].right = root + index;
//            } else {
//                printf("WARNING: data error. type = %d\n", type);
//            }
//        }
//    }
//}

// Decodes your encoded data to tree.
TreeNode* stringToTree(string data) {
  if (data.length() == 2) return NULL;
  vector<string> vec;

  int prePos = 1;
  for (int i = 1; i < data.size(); i++) {
    if (data[i] == ',') {
      vec.push_back(data.substr(prePos, i - prePos));
      prePos = i + 1;
    }
  }
  vec.push_back(data.substr(prePos, data.size() - prePos - 1));

  TreeNode* root = new TreeNode(atoi(vec[0].c_str()));
  queue<TreeNode*> que;
  que.push(root);

  for (int i = 1; i < vec.size();) {
    TreeNode* pre = que.front();
    que.pop();
    if (!pre) continue;
    if (i < vec.size() && vec[i] != "null") {
      pre->left = new TreeNode(atoi(vec[i].c_str()));
      que.push(pre->left);
    }
    i++;

    if (i < vec.size() && vec[i] != "null") {
      pre->right = new TreeNode(atoi(vec[i].c_str()));
      que.push(pre->right);
    }
    i++;
  }
  return root;
}

TreeNode* vecToTree(vector<int> data) {
  if (data.size() == 0) {
    return nullptr;
  }

  TreeNode* root = new TreeNode(data[0]);
  ;
  queue<TreeNode*> que;
  que.push(root);

  for (int i = 1; i < data.size();) {
    TreeNode* preNode = que.front();
    que.pop();

    if (preNode == nullptr) {
      continue;
    }

    // left child
    if (i < data.size()) {
      if (data[i] >= 0) {
        preNode->left = new TreeNode(data[i]);
        que.push(preNode->left);
      } else {
        // que.push(nullptr);
      }
      i++;
    }

    // right child
    if (i < data.size()) {
      if (data[i] >= 0) {
        preNode->right = new TreeNode(data[i]);
        que.push(preNode->right);
      } else {
        // que.push(nullptr);
      }
      i++;
    }
  }

  return root;
}

int countTreeNode(TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + countTreeNode(root->left) + countTreeNode(root->right);
}

int deepTreeNode(TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + max(deepTreeNode(root->left), deepTreeNode(root->right));
}

void printbase(int val, int base) {
  switch (base) {
    case 1:
      printf("%1d", val);
      break;
    case 2:
      printf("%2d", val);
      break;
    case 3:
      printf("%3d", val);
      break;
    case 4:
      printf("%4d", val);
      break;
    case 5:
      printf("%5d", val);
      break;
    default:
      printf("%d", val);
      break;
  }
}
void printbase(string val, int base) {
  switch (base) {
    case 1:
      printf("%1s", val.c_str());
      break;
    case 2:
      printf("%2s", val.c_str());
      break;
    case 3:
      printf("%3s", val.c_str());
      break;
    case 4:
      printf("%4s", val.c_str());
      break;
    case 5:
      printf("%5s", val.c_str());
      break;
    default:
      printf("%s", val.c_str());
      break;
  }
}

void printfblank(int befotnum, int base) {
  while (befotnum-- > 0) {
    printbase("", base);
  }
}

void output(TreeNode* root) {
  int treeCount = countTreeNode(root);
  int deepCount = deepTreeNode(root);
  queue<TreeNode*> que;
  int lev = 0;
  int treenum = 0;
  int levnum = 0;
  int befotnum = 0;
  int betweenNum = 1;
  int base = 1;

  for (int i = 1; i < deepCount; i++) {
    befotnum = betweenNum;
    betweenNum = betweenNum * 2 + 1;
  }

  printf("\n[%2d] :", lev++);
  printfblank(befotnum, base);

  que.push(root);
  while (!que.empty()) {
    TreeNode* pre = que.front();
    que.pop();
    if (pre != nullptr) {
      que.push(pre->left);
      que.push(pre->right);
      printbase(pre->val, base);
      treenum++;
    } else {
      que.push(nullptr);
      que.push(nullptr);
      printbase("-", base);
    }
    levnum++;

    if (treenum >= treeCount) {
      break;
    }

    printfblank(betweenNum, base);
    if ((levnum & (levnum + 1)) == 0) {
      printf("\n[%2d] :", lev++);
      betweenNum = befotnum;
      befotnum = befotnum / 2;
      printfblank(befotnum, base);
    }
  }
  printf("\n");
}

template <class T>
void output(const T& data) = delete;

void output(const char* const& data) { printf("%s ", data); }

void output(const bool& data) { printf("%s ", data ? "true" : "false"); }

void output(const double& data) { printf("%f ", data); }

void output(const char& data) { printf("%c ", data); }

void output(const int& data) { printf("%5d ", data); }

void output(const long long& data) { printf("%lld ", data); }
void output(const string& data) { printf("%s ", data.c_str()); }

template <class FirstType, class SecondType>
void output(const pair<FirstType, SecondType>& data) {
  output("{");
  output(data.first);
  output(": ");
  output(data.second);
  output("}");
}

template <class baseType>
void output(const vector<baseType>& vec) {
  for (int i = 0; i < vec.size(); i++) {
    output(vec[i]);
  }
  // printf("\n");
}

template <class baseType>
void output(const vector<vector<baseType>>& matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    output(matrix[i]);
  }
  // printf("\n");
}

template <class baseType>
void output(char const* name, baseType data) {
  printf("%s:", name);
  output(data);
  printf("\n");
}
template <class baseType>
void output(char const* name, vector<baseType> data) {
  printf("%s size[%3d]:    ", name, data.size());
  output(data);
  printf("\n");
}

template <class vecType>
void output(char const* name, vector<vector<vecType>> data) {
  printf("%s size[%4d]:\n", name, data.size());
  for (int i = 0; i < data.size(); i++) {
    printf("index[%3d] size[%d]", i, data[i].size());
    output(data[i]);
    printf("\n");
  }
  // printf("\n");
}

template <class baseType>
bool eq(baseType first, baseType second) {
  return first == second;
}

template <>
bool eq(double first, double second) {
  double dis = first - second;
  return dis < base_eps && dis > -base_eps;
}

template <>
bool eq(TreeNode* first, TreeNode* second) {
  if (first == NULL && second == NULL) {
    return true;
  }
  if (first == NULL || second == NULL) {
    return false;
  }
  if (first->val != second->val) {
    return false;
  }
  return eq(first->left, second->left) && eq(first->right, second->right);
}
template <>
bool eq(ListNode* first, ListNode* second) {
  set<ListNode*> oneSet;
  set<ListNode*> twoSet;
  while (first && second && first->val == second->val) {
    if (oneSet.find(first) != oneSet.end()) {
      break;
    }
    oneSet.insert(first);
    if (twoSet.find(second) != twoSet.end()) {
      break;
    }
    twoSet.insert(second);
    first = first->next;
    second = second->next;
  }
  if (first == NULL && second == NULL) {
    return true;
  }
  if (first && second && first->val == second->val) {
    return true;
  }
  return false;
}

template <class baseType>
bool eq(vector<baseType> first, vector<baseType> second) {
  if (first.size() != second.size()) {
    return false;
  }
  for (int i = 0; i < first.size(); i++) {
    if (!eq(first[i], second[i])) {
      return false;
    }
  }
  return true;
}

template <class baseType>
bool eq(vector<vector<baseType>> first, vector<vector<baseType>> second) {
  if (first.size() != second.size()) {
    return false;
  }
  for (int i = 0; i < first.size(); i++) {
    if (!eq(first[i], second[i])) {
      return false;
    }
  }
  return true;
}
int getIndex() {
  static int index = 0;
  return index++;
}

#define TEST_SMP1(ClassName, FunNAme, expectAns, firstData) \
  do {                                                      \
    ClassName work;                                         \
    auto tmpFirstData = firstData;                          \
    auto ans = work.FunNAme(tmpFirstData);                  \
    int index = getIndex();                                 \
    bool check = eq(ans, expectAns);                        \
    if (!check) {                                           \
      printf("index %d: NO\n", index);                      \
      output("firstData", firstData);                       \
      output("ans", ans);                                   \
      output("expectAns", expectAns);                       \
    } else {                                                \
      printf("index %d: YES\n", index);                     \
    }                                                       \
    printf("\n");                                           \
  } while (0)

#define TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData) \
  do {                                                                  \
    ClassName work;                                                     \
    auto tmpFirstData = firstData;                                      \
    auto tmpSecondData = secondData;                                    \
    auto ans = work.FunNAme(tmpFirstData, tmpSecondData);               \
    int index = getIndex();                                             \
    bool check = eq(ans, expectAns);                                    \
    if (!check) {                                                       \
      printf("index %d: NO\n", index);                                  \
      output("firstData", firstData);                                   \
      output("secondData", secondData);                                 \
      output("ans", ans);                                               \
      output("expectAns", expectAns);                                   \
    } else {                                                            \
      printf("index %d: YES\n", index);                                 \
    }                                                                   \
    printf("\n");                                                       \
  } while (0)

#define TEST_SMP3(ClassName, FunNAme, expectAns, firstData, secondData, \
                  thirdData)                                            \
  do {                                                                  \
    ClassName work;                                                     \
    auto tmpFirstData = firstData;                                      \
    auto tmpSecondData = secondData;                                    \
    auto tmpThirdData = thirdData;                                      \
    auto ans = work.FunNAme(tmpFirstData, tmpSecondData, tmpThirdData); \
    int index = getIndex();                                             \
    bool check = eq(ans, expectAns);                                    \
    if (!check) {                                                       \
      printf("index %d: NO\n", index);                                  \
      output("firstData", firstData);                                   \
      output("secondData", secondData);                                 \
      output("thirdData", thirdData);                                   \
      output("ans", ans);                                               \
      output("expectAns", expectAns);                                   \
    } else {                                                            \
      printf("index %d: YES\n", index);                                 \
    }                                                                   \
    printf("\n");                                                       \
  } while (0)

#define TEST_SMP4(ClassName, FunNAme, expectAns, firstData, secondData,        \
                  thirdData, fouthData)                                        \
  do {                                                                         \
    ClassName work;                                                            \
    auto tmpFirstData = firstData;                                             \
    auto tmpSecondData = secondData;                                           \
    auto tmpThirdData = thirdData;                                             \
    auto tmpFouthData = fouthData;                                             \
    auto ans =                                                                 \
        work.FunNAme(tmpFirstData, tmpSecondData, tmpThirdData, tmpFouthData); \
    int index = getIndex();                                                    \
    bool check = eq(ans, expectAns);                                           \
    if (!check) {                                                              \
      printf("index[%d] %d: NO\n", __LINE__, index);                           \
      output("firstData", firstData);                                          \
      output("secondData", secondData);                                        \
      output("thirdData", thirdData);                                          \
      output("fouthData", fouthData);                                          \
      output("ans", ans);                                                      \
      output("expectAns", expectAns);                                          \
      printf("\n");                                                            \
      return 0;                                                                \
    } else {                                                                   \
      printf("index %d: YES\n", index);                                        \
    }                                                                          \
  } while (0)
