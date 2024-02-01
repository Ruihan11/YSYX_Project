#include <stdio.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for(i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
        printf("%p  %p\n",cur_name+i,cur_age+i);}

  

    printf("---\n");

    // third way, pointers are just array

    // int pointer 4 bytes, char 8
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
 	printf("%p  %p\n",&cur_name[i],&cur_age[i]);}

    printf("---\n");
    
    //while
    i=0;
    while(i < count) {
        printf("%s is %d years old again.\n",            
                cur_name[i], cur_age[i]);
	i++;
}

    //
    char *add="h";
    printf("%p  %s\n",&add,add);

    return 0;
}
