
/*
ID: tiankonguse
TASK: struct
LANG: C++
CONTEST: CSP-S 2023
qoj: https://qoj.ac/contest/1428/problem/7815
luogu: https://www.luogu.com.cn/problem/P9754
*/
#define TASK "struct"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

class Member {
 public:
  string type;
  string name;
  ll offset;
  Member() { offset = 0; }
  Member(const string& type_, const string& name_, ll offset_ = 0)
      : type(type_), name(name_), offset(offset_) {}
};

class Type {
 public:
  string name;
  ll type_size;
  vector<Member> childs;
  map<string, ll> childName2Index;
  map<ll, ll> offset2Index;
  Type() : type_size(0) {}
  Type(const string& name_, ll type_size_ = 0)
      : name(name_), type_size(type_size_) {}

  Member* AddMember(const string& type_, const string& name_, ll offset_ = 0) {
    this->childs.emplace_back(std::move(Member(type_, name_, offset_)));
    this->childName2Index[name] = childs.size() - 1;
    return &this->childs.back();
  }
  Member* GetMember(const string& name_) {
    if (!childName2Index.count(name_)) return nullptr;
    return &childs[childName2Index[name_]];
  }
  ll GetChildNum() { return childs.size(); }
};
vector<Type> types;
map<string, int> typeName2Index;

Type global;
ll offset = 0;

Type* GetType(const string& name) {
  if (!typeName2Index.count(name)) return nullptr;
  return &types[typeName2Index[name]];
}

Type* AddType(const string& name, ll type_size = 0) {
  types.emplace_back(std::move(Type(name, type_size)));
  typeName2Index[name] = types.size() - 1;
  return &types.back();
}

void Init() {
  AddType("byte", 1);
  AddType("short", 2);
  AddType("int", 4);
  AddType("long", 8);
}

char str[20], type[20], name[20];
void Solver() {  //
  Init();
  ll n;
  scanf("%lld", &n);
  while (n--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int k;
      scanf("%s%lld", &str, &k);
      Type* t = AddType(str);

      ll max_child_size = 0;
      for (int i = 0; i < k; i++) {
        scanf("%s%s", type, name);
        t->AddMember(type, name);
        max_child_size = max(max_child_size, GetType(type)->type_size);
      }
      t->type_size = k * max_child_size;
      for (int i = 0; i < k; i++) {
        ll offset = i * max_child_size;
        t->childs[i].offset = i * max_child_size;
        t->offset2Index[offset] = i;
      }
      printf("%lld %lld\n", t->type_size, max_child_size);
    } else if (op == 2) {
      scanf("%s%s", type, name);
      const Type* t = GetType(type);
      ll type_size = t->type_size;
      offset = (offset + type_size - 1) / type_size * type_size;

      global.AddMember(type, name, offset);
      global.offset2Index[offset] = global.GetChildNum() - 1;

      printf("%lld\n", offset);
      offset += type_size;

    } else if (op == 3) {
      getchar();  // skip space
      string name;
      Type* query_type = &global;
      ll query_offset = 0;
      while (true) {
        char c = getchar();
        if ('a' <= c && c <= 'z') {
          name.push_back(c);
        } else {
          const Member* childMember = query_type->GetMember(name);
          printf("step typeName[%s] typeSize[%lld] from[%lld]",
                 query_type->name.c_str(), query_type->type_size, query_offset);
          query_offset += childMember->offset;
          query_type = GetType(childMember->type);
          printf("->to[%lld] childType[%s]\n", query_offset,
                 childMember->type.c_str());
          name.clear();
          if (c != '.') {
            break;
          }
        }
      }
      printf("%lld\n", query_offset);

    } else {
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
5
1 a 2
short aa
int ab
1 b 2
a ba
long bb
2 b x
3 x.ba.ab
4 10

8 4
16 8
0
4
x.bb
*/