#include <bits/stdc++.h>
using namespace std;
const int N = 110;
char name[N][25];  // 定义一个二维字符数组
int qg, bg;        // 表示两个成绩
char gan, xi;      // 表示是否是干部，是否是西部学生
int num;           // 表示论文的数量
int score[N];      // 每个人总的奖学金
int main() {
  int n, i;
  // memset(score,0,sizeof(int)*N);
  scanf("%d", &n);
  for (i = 0; i < n; i++) {  // 一边输入一边处理
    // scanf("%s %d %d %c %c %d",name[i],qg,bg,gan,xi,num);
    cin >> name[i] >> qg >> bg >> gan >> xi >> num;
    // printf("name=%s qg=%d bg=%d gan=[%c] xi=[%c] num=%d\n", name[i], qg, bg, gan,
    //        xi, num);
    if (qg > 80 && num >= 1) score[i] += 8000;
    if (qg > 85 && bg > 80) score[i] += 4000;
    if (qg > 90) score[i] += 2000;
    if (qg > 85 && xi == 'Y') score[i] += 1000;
    if (qg > 80 && gan == 'Y') score[i] += 850;
  }
  int max = 0;
  int k;
  int totle = 0;
  for (i = 0; i < n; i++) {
    totle += score[i];
    if (score[i] >
        max) {  // 只有后面的比它大才替换，因为说的是要找第一个最多的人
      max = score[i];
      k = i;  // 标记最多的人，找到它的名字
    }
  }
  // printf("%s\n%d\n%d\n",name[k],score[k],totle);
  cout << name[k] << endl << score[k] << endl << totle << endl;
  return 0;
}
