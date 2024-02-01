#include <stdio.h>

int main(int argc, char *argv[])
{
/*
puts("hello");

int integer = 1;
float floatingNum = 2.345f;
char a = 'A';
char string[] = "YSYX is funnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";

printf("int    %d \n",integer);
printf("float  %f \n",floatingNum);
printf("char   %c \n",a);
printf("string %s \n",string);


int i = 2;
double j = 300000;
long k = 1024L*1024L;
char nul_byte = '\0';
int nulll = nul_byte*i;

printf("%f \n",j);
printf("%ld \n",k);
printf("%e \n",j);
printf("%d \n",nulll);
*/

/*
array
only define one number or character - others are 0 or \0
leave the end of string to be \0
*/

int numbers[4] = {1};
char name[4] = {'a'};
printf("numbers:   %d %d %d %d\n",numbers[0], numbers[1],numbers[2], numbers[3]);
printf("name each: %c %c %c %c\n",name[0], name[1],name[2], name[3]);

int numbers1[4] = {1,2,3,4};
char name1[4] = {'a','b','c','d'};
printf("numbers:   %d %d %d %d  \n%ls \n",numbers1[0], numbers1[1],numbers1[2],numbers1[3],numbers1);
printf("name each: %c %c %c %c  \n%s \n",name1[0], name1[1],name1[2], name1[3],name1);

char *haha = "abcde";
printf("%s\n%c\n%c%c%c\n",haha,*haha,haha[0],haha[2],haha[4]);

char *bugtest="bugtest";
printf("bugtest---%s\n",bugtest);
bugtest[7]='h';
printf("bugtest---%s\n",bugtest);









return 0;
}
