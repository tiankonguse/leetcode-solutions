#include "base.h"

class OrderedStream {
  vector<string> vec;
  int ptr;

 public:
  OrderedStream(int n) {
    vec.resize(n + 1);
    ptr = 1;
  }

  vector<string> next() {
    vector<string> ans;

    while (ptr < vec.size() && vec[ptr].length() > 0) {
      ans.push_back(vec[ptr]);
      ptr++;
    }
    return ans;
  }

  vector<string> insert(int id, string value) {
    vec[id] = value;
    return next();
  }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(id,value);
 */
template <class AnsType, class OpreateType, class InitType,
          class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData,
             DataType1 firstData = DataType1()) {
  AnsType ans;
  // OrderedStream work;
  OrderedStream work(initData[0]);  //按需修改

  for (int i = 0; i < opreateParam.size(); i++) {
    if (opreateParam[i] == "insert") {
      auto& p = firstData[i];
      ans.push_back(work.insert(p.first, p.second));
    }
  }
  int index = getIndex();
  bool check = eq(ans, expectAns);
  if (!check) {
    printf("index %d: NO\n", index);
    output("opreateParam", opreateParam);
    output(" initData", initData);
    output("firstData", firstData);
    output("      ans", ans);
    output("expectAns", expectAns);

  } else {
    printf("index %d: YES\n", index);
  }
  printf("\n");
}

int main() {
  vector<string> opreateParam;
  vector<int> initData;
  vector<pair<int, string>> firstData;
  vector<vector<string>> expectAns;

  opreateParam = {"insert", "insert", "insert", "insert", "insert"};
  initData = {5};
  firstData = {
      {3, "ccccc"}, {1, "aaaaa"}, {2, "bbbbb"}, {5, "eeeee"}, {4, "ddddd"}};
  expectAns = {{}, {"aaaaa"}, {"bbbbb", "ccccc"}, {}, {"ddddd", "eeeee"}};
  test_qa(expectAns, opreateParam, initData, firstData);

  return 0;
}
