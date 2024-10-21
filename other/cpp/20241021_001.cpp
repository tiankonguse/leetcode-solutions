#include <bits/stdc++.h>
using namespace std;
int main() {
  vector<vector<string>> records;
  vector<string> names;
  unordered_map<string, int> hash;
  string s1, s2;
  int n, m;
  
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    cin >> s1 >> s2;
    if (hash.count(s1) == 0) {
      hash[s1] = names.size();
      names.push_back(s1);
      records.push_back(vector<string>());
    }
    records[hash[s1]].push_back(s2);
  }

  for (int i = 0; i < names.size(); i++) {
    cout << names[i];
    for (int j = 0; j < records[i].size(); j++) {
      cout << " " << records[i][j];
    }
    printf("\n");
  }

  return 0;
}
