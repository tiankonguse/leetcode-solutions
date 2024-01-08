## Combination Lock 密码锁


Farmer John's cows keep escaping from his farm and causing mischief. To try and prevent them from leaving, he purchases a fancy combination lock to keep his cows from opening the pasture gate.
农夫约翰的奶牛不断逃离他的农场并造成恶作剧。为了阻止他们离开，他购买了一把奇特的密码锁，以防止他的奶牛打开牧场大门。

Knowing that his cows are quite clever, Farmer John wants to make sure they cannot easily open the lock by simply trying many different combinations. The lock has three dials, each numbered 1..N (1 <= N <= 100), where 1 and N are adjacent since the dials are circular.
农夫约翰知道他的奶牛非常聪明，他希望确保它们不能通过简单地尝试许多不同的组合来轻松打开锁。该锁有三个表盘，每个编号为 1..N (1 <= N <= 100)，其中 1 和 N 相邻，因为表盘是圆形的。
There are two combinations that open the lock, one set by Farmer John, and also a "master" combination set by the lock maker.
有两种打开锁的密码，一种是农夫约翰设置的，另一种是锁匠设置的“主”密码。

The lock has a small tolerance for error, however, so it will open even if the numbers on the dials are each within at most 2 positions of a valid combination.
然而，锁的容错能力很小，因此即使转盘上的数字最多位于有效组合的 2 个位置内，锁也会打开。

For example, if Farmer John's combination is (1,2,3) and the master combination is (4,5,6), the lock will open if its dials are set to (1,3,5) (since this is close enough to Farmer John's combination) or to (2,4,8) (since this is close enough to the master combination).
例如，如果 Farmer John 的密码是 (1,2,3)，主密码是 (4,5,6)，如果其拨盘设置为 (1,3,5)，锁就会打开（因为这是关闭的）足以达到农夫约翰的组合）或（2,4,8）（因为这足够接近主组合）。
Note that (1,5,6) would not open the lock, since it is not close enough to any one single combination.
请注意，(1,5,6) 不会打开锁，因为它与任何一种组合都不够接近。

Given Farmer John's combination and the master combination, please determine the number of distinct settings for the dials that will open the lock. Order matters, so the setting (1,2,3) is distinct from (3,2,1).
给定农夫约翰的密码和主密码，请确定将打开锁的表盘的不同设置的数量。顺序很重要，因此设置 (1,2,3) 与 (3,2,1) 不同。

PROGRAM NAME: combo
程序名称：组合
INPUT FORMAT: 输入格式：
Line 1: 1号线：	The integer N. 整数N。
Line 2: 2号线：	Three space-separated integers, specifying Farmer John's combination.
三个空格分隔的整数，指定 Farmer John 的组合。
Line 3: 第 3 行：	Three space-separated integers, specifying the master combination (possibly the same as Farmer John's combination).
三个空格分隔的整数，指定主组合（可能与 Farmer John 的组合相同）。
SAMPLE INPUT (file combo.in):
示例输入（文件combo.in）：
50
1 2 3
5 6 7
INPUT DETAILS: 输入详细信息：
Each dial is numbered 1..50. Farmer John's combination is (1,2,3), and the master combination is (5,6,7).
每个表盘的编号为 1..50。农夫约翰的组合是（1,2,3），大师组合是（5,6,7）。

OUTPUT FORMAT:  输出格式：
Line 1: 1号线：	The number of distinct dial settings that will open the lock.
将打开锁的不同拨号设置的数量。
SAMPLE OUTPUT (file combo.out):
示例输出（文件combo.out）：
249
SAMPLE OUTPUT EXPLANATION
示例输出说明
Here's a list:  这是一个列表：

```

1,1,1  2,2,4  3,4,2  4,4,5  5,4,8  6,5,6  7,5,9  3,50,2  50,1,4 
1,1,2  2,2,5  3,4,3  4,4,6  5,4,9  6,5,7  7,6,5  3,50,3  50,1,5 
1,1,3  2,3,1  3,4,4  4,4,7  5,5,5  6,5,8  7,6,6  3,50,4  50,2,1 
1,1,4  2,3,2  3,4,5  4,4,8  5,5,6  6,5,9  7,6,7  3,50,5  50,2,2 
1,1,5  2,3,3  3,4,6  4,4,9  5,5,7  6,6,5  7,6,8  49,1,1  50,2,3 
1,2,1  2,3,4  3,4,7  4,5,5  5,5,8  6,6,6  7,6,9  49,1,2  50,2,4 
1,2,2  2,3,5  3,4,8  4,5,6  5,5,9  6,6,7  7,7,5  49,1,3  50,2,5 
1,2,3  2,4,1  3,4,9  4,5,7  5,6,5  6,6,8  7,7,6  49,1,4  50,3,1 
1,2,4  2,4,2  3,5,5  4,5,8  5,6,6  6,6,9  7,7,7  49,1,5  50,3,2 
1,2,5  2,4,3  3,5,6  4,5,9  5,6,7  6,7,5  7,7,8  49,2,1  50,3,3 
1,3,1  2,4,4  3,5,7  4,6,5  5,6,8  6,7,6  7,7,9  49,2,2  50,3,4 
1,3,2  2,4,5  3,5,8  4,6,6  5,6,9  6,7,7  7,8,5  49,2,3  50,3,5 
1,3,3  3,1,1  3,5,9  4,6,7  5,7,5  6,7,8  7,8,6  49,2,4  50,4,1 
1,3,4  3,1,2  3,6,5  4,6,8  5,7,6  6,7,9  7,8,7  49,2,5  50,4,2 
1,3,5  3,1,3  3,6,6  4,6,9  5,7,7  6,8,5  7,8,8  49,3,1  50,4,3 
1,4,1  3,1,4  3,6,7  4,7,5  5,7,8  6,8,6  7,8,9  49,3,2  50,4,4 
1,4,2  3,1,5  3,6,8  4,7,6  5,7,9  6,8,7  1,50,1 49,3,3  50,4,5 
1,4,3  3,2,1  3,6,9  4,7,7  5,8,5  6,8,8  1,50,2 49,3,4  49,50,1
1,4,4  3,2,2  3,7,5  4,7,8  5,8,6  6,8,9  1,50,3 49,3,5  49,50,2
1,4,5  3,2,3  3,7,6  4,7,9  5,8,7  7,4,5  1,50,4 49,4,1  49,50,3
2,1,1  3,2,4  3,7,7  4,8,5  5,8,8  7,4,6  1,50,5 49,4,2  49,50,4
2,1,2  3,2,5  3,7,8  4,8,6  5,8,9  7,4,7  2,50,1 49,4,3  49,50,5
2,1,3  3,3,1  3,7,9  4,8,7  6,4,5  7,4,8  2,50,2 49,4,4  50,50,1
2,1,4  3,3,2  3,8,5  4,8,8  6,4,6  7,4,9  2,50,3 49,4,5  50,50,2
2,1,5  3,3,3  3,8,6  4,8,9  6,4,7  7,5,5  2,50,4 50,1,1  50,50,3
2,2,1  3,3,4  3,8,7  5,4,5  6,4,8  7,5,6  2,50,5 50,1,2  50,50,4
2,2,2  3,3,5  3,8,8  5,4,6  6,4,9  7,5,7  3,50,1 50,1,3  50,50,5
2,2,3  3,4,1  3,8,9  5,4,7  6,5,5  7,5,8
```