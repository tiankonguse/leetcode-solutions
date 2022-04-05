# 584. 寻找用户推荐人

给定表  customer  ，里面保存了所有客户信息和他们的推荐人。

```
+------+------+-----------+
| id   | name | referee_id|
+------+------+-----------+
|    1 | Will |      NULL |
|    2 | Jane |      NULL |
|    3 | Alex |         2 |
|    4 | Bill |      NULL |
|    5 | Zack |         1 |
|    6 | Mark |         2 |
+------+------+-----------+
```


写一个查询语句，返回一个客户列表，列表中客户的推荐人的编号都  不是 2。

对于上面的示例数据，结果为：


```
+------+
| name |
+------+
| Will |
| Jane |
| Bill |
| Zack |
+------+
```


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-customer-referee
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
