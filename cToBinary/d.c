#include <stdio.h>
int main() {
	  printf(1-2147483648 > 0 ? "T" : "F");
	//    printf(6 - 0x80000000 > 6 ? "T" : "F");
	//      printf("\n");
	        return 0;
}


/*
clang -w -std=c99 -m32 d.c&& ./a.out
clang -w -std=c99 -m64 d.c&& ./a.out
clang -w -std=c90 -m32 d.c&& ./a.out
clang -w -std=c90 -m64 d.c&& ./a.out
*/