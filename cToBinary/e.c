#include <stdio.h>
int main() {
  printf("%zu\n", sizeof(long));
  return 0;
}
/*
clang -w -m32 e.c && ./a.out
clang -w -m64 e.c && ./a.out
*/