#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LINE_MAX 20001
#define MAX_COUNT 10000
#define THREAD_COUNT 3
int  count(FILE * fp);
int* each_length(FILE * fp, int length);
void textfile_parser(char **buffer, int **unsorted_array, int *each_items_count, FILE *fp_in, int count);
void merge(int *arr, int l, int m, int r);
void mergesort(int *arr, int l, int r);
void printArray(int *A, int size);
void Multithread_MergeSort(int *arr, int length);

typedef struct
{
    int from_index;
    int to_index;
    int *arr;

} parameters;

int main (int argc, char *argv[]) {
    
    FILE *fp_in, *fp_count, *fp_out;
    
    char *in_file, *out_file;
    
    in_file = argv[1]; // in_file <=== input.txt
    
    out_file = argv[2]; // out_file <=== output.txt
    
    fp_in = fopen(in_file, "r");
    
    if (fp_in == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    fp_count = fopen(in_file, "r");
    
    int count_lines = count(fp_count);
    
    fp_count = fopen(in_file, "r");
    
    int* count_each_lines = each_length(fp_count, count_lines);
    
    fp_out = fopen(out_file, "w");    
    
    char **buffer = malloc(count_lines*sizeof(char*));
    
    for(int i = 0; i < count_lines; i++) {
        buffer[i] = malloc(count_each_lines[i]*sizeof(char*));
    }
    
    int **unsorted_array = malloc(count_lines*sizeof(int*));
    
    for(int i = 0; i < count_lines; i++) {
        unsorted_array[i] = malloc(count_each_lines[i]*sizeof(int*));
    }
    
    textfile_parser(buffer, unsorted_array, count_each_lines,fp_in, count_lines);
    
    /*Body begin*/
    printf("\nMerge Sort Begins\n\n");
    
    for(int i = 0; i < count_lines; i++) {
    
        double time_spent = 0.0;
    
        clock_t begin = clock();
    
        /*Merge sort begin*/
        Multithread_MergeSort(unsorted_array[i], count_each_lines[i]);
        //mergesort(unsorted_array[i], 0, count_each_lines[i]-1);
        printArray(unsorted_array[i], count_each_lines[i]);    
        /*Merge sort end*/
        
        clock_t end = clock();
        
        time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
        
        printf("Duration: %f \n", time_spent);
        
        /*Write to output.txt*/
        for(int j = 0; j < count_each_lines[i]; j++) {
 
            fprintf(fp_out, "%d ", unsorted_array[i][j]);
        }
        
        fprintf(fp_out, "\nduration: %f\n\n", time_spent);
    }
    /*Body end*/
    
    fclose(fp_in);
    fclose(fp_count);
    fclose(fp_out);
    return 0;
}

int count(FILE * fp) {
    
    /* Count numbers of line */
    char chr = getc(fp);
    
    int count_lines = 0;
    
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr== '\n')
        {
    
            count_lines = count_lines + 1;
    
        }
    
        //take next character from file.
        chr = getc(fp);
    
    }
    
    return count_lines;
}

int* each_length(FILE * fp, int length) {
    
    char chr = getc(fp);
    
    int i = 0;
    
    int *count_each_lines = malloc(length*sizeof(int *));
    
    for(int i = 0; i < length; i ++) count_each_lines[i] = 0;
    
    while (chr != EOF)
    {
    
        if(chr == ' ') {
    
            count_each_lines[i] += 1;
    
        }
    
        //Count whenever new line is encountered
        if (chr== '\n')
        {
    
            count_each_lines[i] += 1;
    
            i += 1;
        }
    
        //take next character from file.
        chr = getc(fp);
    }
    
    return count_each_lines;
}

void textfile_parser(char **buffer, int **unsorted_array, int *count_each_lines, FILE *fp_in, int count_lines) {
    int i = 0;
    
    while(fgets(buffer[i], LINE_MAX, fp_in)) 
	{
    
        buffer[i][strlen(buffer[i]) - 1] = '\0';
    
        int ipos = 0;
    
        // Get the first token from the string
        char *token = strtok(buffer[i], " ");
    
        // Keep going until we run out of tokens
        while (token != NULL) {
    
            // Don't overflow your target array
            if (ipos < MAX_COUNT) {
    
                // Convert to integer and store it
                unsorted_array[i][ipos++] = atoi(token);
    
            }
    
            // Get the next token from the string - note the use of NULL
            // instead of the string in this case - that tells it to carry
            // on from where it left off.
    
            token = strtok(NULL, " ");
        }
    
        i++;
    }

    /*Parse Checker*/
    for(int i = 0; i < count_lines; i++) {
    
        printf("Line %d: %d items\n", i+1, count_each_lines[i]);
    
        for(int j = 0; j < count_each_lines[i]; j++) {
    
            printf("%d ", unsorted_array[i][j]); 
        }
            printf("\n");
    }
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int *arr, int l, int m, int r) 
{ 
    int i, j, k; 

    int n1 = m - l + 1;

    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 

    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    
    i = 0; // Initial index of first subarray 
    
    j = 0; // Initial index of second subarray 
    
    k = l; // Initial index of merged subarray 
    
    while (i < n1 && j < n2) 
    { 
    
        if (L[i] <= R[j]) 
        { 
    
            arr[k] = L[i]; 
    
            i++; 
    
        } 
    
        else
        { 
    
            arr[k] = R[j]; 
    
            j++; 
        } 
    
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
    
        arr[k] = L[i]; 
    
        i++; 
    
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
    
        arr[k] = R[j]; 
    
        j++; 
    
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergesort(int *arr, int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergesort(arr, l, m); 
        mergesort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
  
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int *A, int size) 
{ 
    int i; 

    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    
    printf("\n"); 
}

void *sortArray(void *params)

{

    parameters* p = (parameters *)params;

    //SORT

    int begin = p->from_index;

    int end = p->to_index;

    int *array = p->arr;

    mergesort(array, begin, end);

    pthread_exit(0);
}

void *mergeArray(void *params) {
    
    parameters* p = (parameters *)params;

    //MERGE

    int begin = p->from_index;

    int end = p->to_index;

    int middle = begin +(end-begin)/2;

    int* array = p->arr;

    merge(array, begin, middle, end);

    pthread_exit(0);

}

void Multithread_MergeSort(int *arr, int length) {
    pthread_t threads[THREAD_COUNT];

    /* establish the first sorting thread */

    parameters *data = (parameters *) malloc (sizeof(parameters));

    data->from_index = 0;

    data->to_index = 0 + ((length-1)/2);
    printf("middle: %d\n", data->to_index);

    data->arr = arr;

    pthread_create(&threads[0], 0, sortArray, data);
        /* establish the second sorting thread */

    data = (parameters *) malloc (sizeof(parameters));

    data->from_index = ((length-1)/2) + 1;

    data->to_index = length - 1;

    data->arr = arr;

    pthread_create(&threads[1], 0, sortArray, data);

    /* now wait for the 2 sorting threads to finish */

    for (int i = 0; i < THREAD_COUNT - 1; i++)

        pthread_join(threads[i], NULL);

    /* establish the merge thread */

    data = (parameters *) malloc(sizeof(parameters));

    data->from_index = 0;

    data->to_index = length - 1;

    data->arr = arr;

    pthread_create(&threads[2], 0, mergeArray, data);

    /* wait for the merge thread to finish */

    pthread_join(threads[2], NULL);

}