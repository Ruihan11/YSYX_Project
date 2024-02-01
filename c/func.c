#include <stdio.h>
#include <ctype.h>
#include <string.h>
// forward declarations

void print_letters(char arg[],int len);

void print_arguments(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++) {
	printf("arguement %d\n",i);
        print_letters(argv[i],strlen(argv[i]));
    }
}

void print_letters(char arg[],int len)
{
    for(int i = 0;i<len; i++) {
        char ch = arg[i];

        printf("'%c' == %d ", ch, ch);
    }

    printf("\n");
}


int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
