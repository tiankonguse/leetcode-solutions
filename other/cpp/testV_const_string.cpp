#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

void test1() {
  const char* p = "hello word";
  for (const char* i = p; *i; i++) {
    printf("%c", *i);
  }
  printf("\n");
}

int main() {
  const int N = 2;
  int a[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      a[i][j] = i * N + j;
    }
  }

  typedef int* int1;
  int1 p1[N];
  for (int i = 0; i < N; i++) {
    p1[i] = a[i];
  }
  for (int i = 0; i < N; i++) {
    printf("*p1[%d]=%d\n", i, *p1[i]);
    for (int j = 0; j < N; j++) {
      printf("p1[%d][%d]=%d\n", i, j, p1[i][j]);
    }
  }
  printf("\n");

  typedef int(*int10)[N];
  int10 p2[N];
  for (int i = 0; i < N; i++) {
    p2[i] = &a[i];  // 由于指向 int(*)[N]， 必须加引号
  }
  for (int i = 0; i < N; i++) {
    printf("*p2[%d]=%p **p2[%d]=%d\n", i, *p2[i], i, **p2[i]);
    for (int j = 0; j < N; j++) {
      printf("p2[%d][%d]=%p *p2[%d][%d]=%d\n", i, j, p2[i][j], i, j, *p2[i][j]);
    }
  }
  printf("\n");

  return 0;
}