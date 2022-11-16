#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>//用tree
#include<ext/pb_ds/hash_policy.hpp>//用hash
#include<ext/pb_ds/trie_policy.hpp>//用trie
#include<ext/pb_ds/priority_queue.hpp>//用priority_queue

// 参考资料1: https://www.luogu.com.cn/blog/Chanis/gnu-pbds
// 参考资料2: https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/
// 参考资料3: https://codeforces.com/blog/entry/11080


using namespace __gnu_pbds;

// tree<类型, 无映射, 排序方式, 红黑树, 更新方式>
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

ordered_set<int> tr;

tr.insert(v); //插入;
tr.erase(v)); //删除;
tr.order_of_key(x); //求排名 
tr.find_by_order(k); //找k小值，返回迭代器 
tr.lower_bound(x); //返回第一个大于等于x的元素的迭代器
tr.upper_bound(x); //返回第一个大于x的元素的迭代器
//以上所有操作的时间复杂度均为O(logn) 
