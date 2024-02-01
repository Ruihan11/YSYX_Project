#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);
typedef int *(*algo)(int *number,int count,compare_cb cmp);
/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */



int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));
    //bubble the near 2 int
    for(i = 0; i < count; i++) {
        for(j = 0; j < count - 1; j++) {
            if(cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int *insert_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    
    int *target = malloc(count * sizeof(int));
    int *arr = malloc(count * sizeof(int));
    if(!target) die("Memory error.");
    target[0]= numbers[0];

    // printf("\n");
    // for(int w = 0; w < count; w++) {printf("%d ",target[w]);}
    // printf("\n\n");

    for(i = 1; i < count; i++) {
        // printf("i %d \n",i);
        target[i]=numbers[i];
        temp=target[i]; //the insert candidate

        // printf("\n");
        // for(int w = 0; w < count; w++) {printf("%d ",target[w]);}
        // printf("\n\n");

        // printf("candidate %d \n",temp);

        for(j = 0; j < i; j++) {
            // printf("  j %d \n",j);
            if(cmp(temp,target[j]) > 0) {
                // printf("  comparing %d \n",target[j]);
                //insert and the array move right
                arr[j]=temp;
                for (int k = 0;k<j;k++){arr[k]=target[k];}
                for (int q = j+1;q<i+1;q++){arr[q]=target[q-1];}
                memcpy(target, arr, (i+1) * sizeof(int));
                break;
            }

        }
        // printf("\n");
        // for(int w = 0; w < count; w++) {printf("%d ",target[w]);}
        // printf("\n\n");
    }
    free(arr);
    return target;
    
}


int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp,algo al)
{
    int i = 0;
    int *sorted = al(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    free(sorted);

    // unsigned char *data = (unsigned char *)cmp;
    // for(i = 0; i < 25; i++) {
    // printf("%02x:", data[i]);
    // }
    // printf("\n");
}


int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int)); //num of ints 
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        // printf("%s\n",inputs[i]);
        numbers[i] = atoi(inputs[i]);
    }

    // test_sorting(numbers, count, sorted_order,bubble_sort);
    // test_sorting(numbers, count, reverse_order,bubble_sort);
    // test_sorting(numbers, count, strange_order,bubble_sort);

    test_sorting(numbers, count, sorted_order,insert_sort);
    test_sorting(numbers, count, reverse_order,insert_sort);
    // test_sorting(numbers, count, strange_order,insert_sort);
    

    free(numbers);

    return 0;
}


/*
./exe 3 2 1
./exe 1 2 3
*/