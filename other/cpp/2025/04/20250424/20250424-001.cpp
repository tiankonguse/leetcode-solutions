#include<bits/stdc++.h>
using namespace std;
struct HTNode { //单个结点的信息
    int weight; //权值
    char value[2]; //结点的信息
    int parent; //父结点
    int lChild; //左孩子
    int rChild;//右孩子
};
// 选择权值最小的两颗树
void SelectMin(HTNode *hT, int i, int &s1, int &s2) {
    int min = INT_MAX; //INT_MAX是一个很大的数，要使用头文件limits
    for (int j = 1; j <= i; j++) {
        //如果第j个元素的weight值小于min，且第j个元素的双亲值为0
        //则将该值赋给min,j赋值给是s1
        if ( hT[j].weight < min && hT[j].parent == -1) {
            min = hT[j].weight;
            s1 = j;
        }
    }

    min = INT_MAX; //重新给min赋值
    for (int j = 1; j <= i; j++) {
        //如果第j个元素的weight值小于min，且j不等于s1，且第j个元素的双亲值为0
        //则将该值赋给min,j赋值给是s2
        if (hT[j].weight<min && j != s1 && hT[j].parent == -1) {
            min = hT[j].weight;
            s2 = j;
        }
    }
}
void CreateHufmanTree(HTNode *hT,int n,int m ) {
    for(int i=n+1; i<=m; i++) {
        int s1,s2;//两个权值最小的结点
        s1=s2=0;
        SelectMin(hT, i, s1, s2);//选取当前根节点权值最小的两棵树
        hT[s1].parent = hT[s2].parent = i; //更新父亲结点
        hT[i].lChild = s1;
        hT[i].rChild = s2;    // 作为新节点的孩子
        hT[i].weight = hT[s1].weight + hT[s2].weight;    // 新节点为左右孩子节点权值之和
    }

}
// 输出哈夫曼树各节点的状态
void Print(HTNode *hT,int m) {
    for(int i = 1; i <= m; ++ i) {
        printf("%5d ",i);
        printf("%5d ",hT[i].weight);
        printf("%5d ",hT[i].parent);
        printf("%5d ",hT[i].lChild);
        printf("%5d ",hT[i].rChild);
        printf("%5s\n",hT[i].value);
    }
}

int main() {
    //初始化哈夫曼树
    int n; //m个结点
    scanf("%d",&n);
    int m=2*n-1; //哈夫曼树总的结点数
    HTNode *hT=new HTNode[m + 1];  //动态生成有m+1个元素的结构体数组。
    for(int i=1; i<=m; i++) { //从数组下标为1开始
        scanf("%d%s",&hT[i].weight,hT[i].value); //结点的权重
        hT[i].parent = hT[i].lChild = hT[i].rChild = -1; //初始化
    }
    //构建哈夫曼树
    CreateHufmanTree(hT,n,m);
    //打印哈夫曼树
    Print(hT,m);
    return 0;
}
/*
4
7 a
5 b
2 c
4 d
*/