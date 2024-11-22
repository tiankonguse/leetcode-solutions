#include <bits/stdc++.h>

int a;    // int   存的是 int 数字
int* pa;  // int*  存的是 int类型的地址
// p[i] <==> *(p+i)
void TestPointInt() {
  a = 10;
  pa = &a;
  printf("*pa=%d\n", *pa);
  printf("pa[0]=%d\n", pa[0]);
}

// int[3] 长度为3的值类型为 int 的元素, a10 指向第一个int的地址
//        0x01  0x02  0x03  0x04
// a10 ->   []    []    []    ?
// a10=>0x01
// a10+1=>0x02, 思考：为何不是 0x04
int a10[3] = {11, 22, 33};
// a10 操作的时候，类型是 int*， 不是 int[3]
void TestA10Point() {
  printf("a10[i]: ");
  for (int i = 0; i < 3; i++) {
    printf("%d%c", *(a10 + i), i + 1 == 3 ? '\n' : ' ');
  }
  printf("pa[i]: ");
  pa = a10;
  for (int i = 0; i < 3; i++) {
    printf("%d%c", pa[i], i + 1 == 3 ? '\n' : ' ');
  }
};

// (int*)[3]  长度为3的值类型为 int* 的元素, a10p 指向第一个 int* 的地址
int* a10p[3];
void TestA10IntPoint() {
  int a = 111;
  int b = 222;
  int c = 333;
  a10p[0] = &a;
  a10p[1] = &b;
  a10p[2] = &c;

  // p[i] <==> *(p+i)
  //  a10p[i] => *(a10p+i)
  // *a10p[i] => * (*(a10p+i))
  printf("a10p[i][0]: ");
  for (int i = 0; i < 3; i++) {
    int* p = a10p[i];
    printf("%d%c", p[0], i + 1 == 3 ? '\n' : ' ');
    // printf("%d%c", a10p[i][0], i + 1 == 3 ? '\n' : ' ');
  }
  printf("*a10p[i]: ");
  for (int i = 0; i < 3; i++) {
    int* p = a10p[i];
    printf("%d%c", *p, i + 1 == 3 ? '\n' : ' ');
    // printf("%d%c", *(a10p[i]), i + 1 == 3 ? '\n' : ' ');
  }
  printf("*(*(a10p+i)): ");
  for (int i = 0; i < 3; i++) {
    int* p = *(a10p + i);
    printf("%d%c", *p, i + 1 == 3 ? '\n' : ' ');
    // printf("%d%c", *(*(a10p + i)), i + 1 == 3 ? '\n' : ' ');
  }
}

// int[3][2] 长度为 3 的值类型为 int[2] 的元素，aa10 指定第一个 int[2] 的元素
//        0x01  0x02
// aa10 ->  []    []
//        0x03  0x04
//          []    []
//        0x05  0x06
//          []    []
// a10=>0x01
// a10+1=>0x03, 思考：为何不是 0x02，为啥不是 0x07
// 数组名不是指针
// 指针有自己的内存空间，储存的是其他类型的地址
//     aa10 => 0x01, 类型 int[2]
//  aa10[i] => 0x01, 类型 int
int aa10[3][2];
/*
aa10->{[ ][ ]} aa10[0] -> {[]}[]  &aa10[0] -> {[ ][ ]}
       [ ][ ]
       [ ][ ]
*/

void TestAA10() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      aa10[i][j] = i * 10 + j;
    }
  }
  for (int i = 0; i < 3; i++) {
    printf("aa10[i][j] i=%d: ", i);
    for (int j = 0; j < 2; j++) {
      printf("%02d ", aa10[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  int* pp;  // 指向长度为 int 的地址
  for (int i = 0; i < 3; i++) {
    printf("int*=%d: ", i);
    pp = aa10[i];  //
    for (int j = 0; j < 2; j++) {
      printf("%02d ", pp[j]);
    }
    printf("\n");
  }
  printf("\n");

  int(*p)[2];  // 指向长度为 int[2] 的地址
  for (int i = 0; i < 3; i++) {
    printf("aa10 + i=%d: ", i);
    p = aa10 + i;  //
    for (int j = 0; j < 2; j++) {
      printf("%02d ", (*p)[j]);
    }
    printf("\n");
  }
  printf("\n");

  // p[i] <==> *(p+i)
  //   int(*p)[2];  // 指向长度为 int[2] 的地址

  printf("int(*)[2] type=%s\n", typeid(p).name());

  printf("aa10[0] type=%s\n", typeid(aa10[0]).name());
  printf("&aa10[0] type=%s\n", typeid(&aa10[0]).name());
  for (int i = 0; i < 3; i++) {
    printf("i=%d: ", i);
    p = &aa10[i];  // aa10[i] 指向 int[2] 数组的首地址
    for (int j = 0; j < 2; j++) {
      printf("%02d ", (*p)[j]);
    }
    printf("\n");
  }
}

int (*d)[3];  //

// int b[10];      // int[10]
// int c[10][10];  // int[10][10]

int main() {
  //   printf("a type=%s\n", typeid(a).name());
  //   printf("&a type=%s\n", typeid(&a).name());
  //   printf("pa type=%s\n", typeid(pa).name());
  //   printf("&pa type=%s\n", typeid(&pa).name());
  //   printf("a10 type=%s\n", typeid(a10).name());
  //   printf("&a10 type=%s\n", typeid(&a10).name());
  TestAA10();
  return 0;
}
