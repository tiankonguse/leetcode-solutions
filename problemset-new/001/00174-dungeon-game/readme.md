# Dungeon Game  174. 地下城游戏

一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

为了尽快到达公主，骑士决定每次只向右或向下移动一步。

说明:

骑士的健康点数没有上限。

任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/dungeon-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。




The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon.   
The dungeon consists of M x N rooms laid out in a 2D grid.   
Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.  


The knight has an initial health point represented by a positive integer.   
If at any point his health point drops to 0 or below, he dies immediately.  


Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms;  
other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).  


In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.  


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.  

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path `RIGHT-> RIGHT -> DOWN -> DOWN`.  

```
---------------------
-2(K) | -3  | 3     |
------|-----|-------|
-5    | -10 | 1     |
------|-----|-------|
10    |  30 | -5 (P)|
---------------------
```

Notes:  

The knight's health has no upper bound.  
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.  




