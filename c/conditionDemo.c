
#include<string.h>
#include<stdio.h>

int main(int argc, char *argv[])
{

//go through argc and print cmd
int i = 0;
while(i<argc){printf("arguement %d: %s\n",i,argv[i]);i++;}
/*
//forward loop
printf("---forward---\n");
int j = 0;
char *list[]={"str1","str2","str3","str4"};
while(j<4){printf("list %d: %s\n",j,list[j]);j++;}
//backward loop
j--;
printf("---backward---\n");
while(j>-1){printf("list %d: %s\n",j,list[j]);j--;}

*/

/*
if(strcmp(argv[1],"1")==0){printf("get 1\n");}
else if(strcmp(argv[1],"2")==0){printf("get 2\n");}
else if(strcmp(argv[1],"3")==0){printf("get 3\n");}
else{printf("naaaa\n");}
*/

char letter = *argv[1];
switch(letter)
{
case 'a':
case 'A':
	printf("A\n");
	break;

case 'b': 
case 'B':
	printf("B\n");
	break;
default:
	printf("This is a default line\n");


}



return 0;
}
