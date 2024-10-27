
/*
ID: tiankonguse
TASK: struct
LANG: C++
CONTEST: CSP-S 2023
qoj: https://qoj.ac/contest/1428/problem/7815
luogu: https://www.luogu.com.cn/problem/P9754
*/
#define TASK "struct3"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll debug = 0;
#define myprintf(...)                        \
  do {                                       \
    if (debug) fprintf(stdout, __VA_ARGS__); \
  } while (0)

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
  // #endif
}

class Member {
 public:
  string type;
  string name;
  ll offset;
  Member(const string& type_ = "", const string& name_ = "", ll offset_ = 0)
      : type(type_), name(name_), offset(offset_) {}
};

class Type {
 public:
  bool base_type;
  ll type_size;
  ll align_size;
  const std::string type_name;
  vector<Member> childs;
  std::unordered_map<string, ll> childName2Index;
  std::map<ll, ll> offset2Index;  // 储存成员的起始位置
  Type(const string& type_name_ = "", const ll type_size_ = 0,
       const bool base_type_ = false)
      : type_name(type_name_) {
    type_size = type_size_;
    align_size = type_size_;  // 默认对齐大小与类型大小一致
    base_type = base_type_;
  }

  const Member* AddMember(const string& child_name_, const class Type* child_) {
    if (childName2Index.count(child_name_)) {
      assert(1);
    }
    assert(child_);
    const std::string& child_type = child_->type_name;
    const ll child_size = child_->type_size;
    const ll child_align = child_->align_size;

    this->align_size = max(this->align_size, child_align);

    ll offset = this->type_size;
    offset = (offset + child_align - 1) / child_align * child_align;
    // myprintf(
    //     "Type[%s] add member[%lld]: childType[%s] childName[%s] "
    //     "childSize[%lld] "
    //     "childAlignSize[%lld] childOffset[%lld] max_align_size[%lld]\n",
    //     this->type_name.c_str(), ll(childs.size()), child_type.c_str(),
    //     child_name_.c_str(), child_size, child_align, offset,
    //     this->align_size);

    this->childs.push_back(Member(child_type, child_name_, offset));
    this->childName2Index[child_name_] = childs.size() - 1;
    this->offset2Index[offset] = childs.size() - 1;

    this->type_size = offset + child_->type_size;
    return &this->childs.back();
  }
  void EndMember() {
    this->type_size = (this->type_size + this->align_size - 1) /
                      this->align_size * this->align_size;
  }
  const Member* GetMember(const string& name_) const {
    auto it = childName2Index.find(name_);
    if (it == childName2Index.end()) return nullptr;
    return &childs[it->second];
  }
  ll GetChildNum() const { return childs.size(); }
};
vector<Type> types;
unordered_map<string, ll> typeName2Index;

Type* GetType(const string& name) {
  auto it = typeName2Index.find(name);
  if (it == typeName2Index.end()) return nullptr;
  return &types[it->second];
}

Type* AddType(const string& name, const ll type_size, const bool base_type) {
  types.push_back(Type(name, type_size, base_type));
  typeName2Index[name] = types.size() - 1;
  return &types.back();
}

const std::string kGlobal = "global";
void Init() {
  AddType("byte", 1, true);
  AddType("short", 2, true);
  AddType("int", 4, true);
  AddType("long", 8, true);
  AddType(kGlobal, 0, false);
}

void Solver() {  //
  char define_type_name[300];
  char child_type[300];
  char child_name[300];
  Init();

  ll n;
  scanf("%lld", &n);
  while (n--) {
    ll op;
    scanf("%lld", &op);
    if (op == 1) {
      ll k;
      scanf("%s%lld", &define_type_name, &k);

      myprintf(
          "n[%lld] op[1], str[%s] k[%lld] globalName[%s][%p] child[%lld] "
          "offset2Index[%lld] childName2Index[%lld]\n",
          n, define_type_name, k, GetType(kGlobal)->type_name.c_str(),
          GetType(kGlobal), ll(GetType(kGlobal)->childs.size()),
          ll(GetType(kGlobal)->offset2Index.size()),
          ll(GetType(kGlobal)->childName2Index.size()));
      Type* t = AddType(define_type_name, 0, false);
      assert(t);
      for (ll i = 0; i < k; i++) {
        scanf("%s%s", &child_type, &child_name);
        const Type* childType = GetType(child_type);
        assert(GetType(kGlobal)->type_name.c_str());
        assert(childType);
        t->AddMember(child_name, childType);
        assert(GetType(kGlobal)->type_name.c_str());
      }
      t->EndMember();
      assert(GetType(kGlobal)->type_name.c_str());
      myprintf(
          "add type[%s] childNum[%lld] offset2Index[%lld] "
          "childName2Index[%lld]\n",
          t->type_name.c_str(), ll(t->childs.size()),
          ll(t->offset2Index.size()), ll(t->childName2Index.size()));
      printf("%lld %lld\n", t->type_size, t->align_size);
    } else if (op == 2) {
      scanf("%s%s", &child_type, &child_name);

      myprintf(
          "n[%lld] op[2], type[%s] name[%s] globalName[%s][%p] child[%lld] "
          "offset2Index[%lld] childName2Index[%lld]\n",
          n, child_type, child_name, GetType(kGlobal)->type_name.c_str(),
          GetType(kGlobal), ll(GetType(kGlobal)->childs.size()),
          ll(GetType(kGlobal)->offset2Index.size()),
          ll(GetType(kGlobal)->childName2Index.size()));
      const Type* childType = GetType(child_type);
      assert(childType);
      const Member* member = GetType(kGlobal)->AddMember(child_name, childType);
      printf("%lld\n", member->offset);
    } else if (op == 3) {
      myprintf(
          "n[%lld] op[3],  globalName[%s][%p] child[%lld] "
          "offset2Index[%lld] childName2Index[%lld]\n",
          n, GetType(kGlobal)->type_name.c_str(), GetType(kGlobal),
          ll(GetType(kGlobal)->childs.size()),
          ll(GetType(kGlobal)->offset2Index.size()),
          ll(GetType(kGlobal)->childName2Index.size()));
      getchar();  // skip space
      string name;
      const Type* query_type = GetType(kGlobal);
      ll query_offset = 0;
      while (true) {
        const char c = getchar();
        if ('a' <= c && c <= 'z') {
          name.push_back(c);
        } else {
          myprintf("step typeName[%s] typeSize[%lld] from[%lld] name[%s]\n",
                   query_type->type_name.c_str(), query_type->type_size,
                   query_offset, name.c_str());
          const Member* childMember = query_type->GetMember(name);
          query_offset += childMember->offset;
          myprintf("->to[%lld] childType[%s] ChidName[%s]\n", query_offset,
                   childMember->type.c_str(), name.c_str());
          if (c != '.') {
            break;
          }
          name.clear();
          query_type = GetType(childMember->type);
        }
      }
      printf("%lld\n", query_offset);
    } else {
      ll query_offset = 0;
      scanf("%lld", &query_offset);
      myprintf(
          "n[%lld] op[4], query_offset[%lld] globalName[%s][%p] child[%lld] "
          "offset2Index[%lld] childName2Index[%lld]\n",
          n, query_offset, GetType(kGlobal)->type_name.c_str(),
          GetType(kGlobal), ll(GetType(kGlobal)->childs.size()),
          ll(GetType(kGlobal)->offset2Index.size()),
          ll(GetType(kGlobal)->childName2Index.size()));
      if (query_offset >= GetType(kGlobal)->type_size) {
        printf("ERR\n");
        continue;
      }

      const Type* query_type = GetType(kGlobal);
      string path;
      while (true) {  // query_offset 已修正，代表 query_type 的偏移量
        auto it = query_type->offset2Index.upper_bound(query_offset);
        it--;                              //
        const ll childIndex = it->second;  // 如果 offset 很大，则指向最后一个
        const Member& member = query_type->childs[childIndex];
        const ll child_offset = member.offset;
        const std::string& child_name = member.name;
        const Type* child_type = GetType(member.type);
        assert(child_type);
        query_offset -= child_offset;
        if (query_offset >= child_type->type_size) {  // 在空洞
          printf("ERR\n");
          break;
        }
        path.append(child_name);
        query_type = child_type;
        if (query_type->base_type) {
          // if (query_offset != 0) {
          //   printf("ERR\n");  // 不在起始位置
          // break;
          // }
          printf("%s\n", path.c_str());
          break;
        }
        path.push_back('.');
      }
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