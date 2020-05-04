#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LINE_MAX 200000
#define THREAD_COUNT 3
int  count(FILE * fp);
int* each_length(FILE * fp, int length);
void textfile_parser(char **buffer, int **unsorted_array, int *each_items_count, FILE *fp_in, int count);
void merge(int *arr, int l, int m, int r);
void mergesort(int *arr, int l, int r);
void printArray(int *A, int size);
void Multithread_MergeSort(int *arr, int length);

/* A single argument that will be passed to start_routine in pthread_create*/
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
        buffer[i] = malloc(LINE_MAX*sizeof(char*));

        printf("%d\n", (int)strlen(buffer[i]));
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
    
    while (chr != EOF) {
        //Count whenever new line is encountered
        if (chr== '\n') {
    
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
    
    while (chr != EOF) {
    
        if(chr == ' ') {
    
            count_each_lines[i] += 1;
    
        }
    
        if (chr== '\n') {
    
            count_each_lines[i] += 1;
    
            i += 1;
        }
    
        chr = getc(fp);
    }
    
    return count_each_lines;
}

void textfile_parser(char **buffer, int **unsorted_array, int *count_each_lines, FILE *fp_in, int count_lines) {
    
    int i = 0;
    
    while(fgets(buffer[i], LINE_MAX, fp_in)) {
    
        buffer[i][strlen(buffer[i]) - 1] = '\0'; //replace '\n' with '\0'
       
        int ipos = 0;
    
        // Get the first token from the string
        char *token = strtok(buffer[i], " ");
    
        // Fetch until there's no token
        while (token != NULL) {
    
            // Don't overflow the target array
            if (ipos < count_each_lines[i]) {
    
                // Convert to integer and store it
                unsorted_array[i][ipos++] = atoi(token);
    
            }
    
            // Get the next token from the string
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
 
void merge(int *arr, int l, int m, int r) 
{ 
    int i, j, k; 

    int n1 = m - l + 1;

    int n2 =  r - m; 
  
    // Create temp arrays
    int L[n1], R[n2]; 
  
    // Copy data to temp arrays L[] and R[] 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 

    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    
    i = 0; // Initial index of first subarray 
    
    j = 0; // Initial index of second subarray 
    
    k = l; // Initial index of merged subarray 
    
    while (i < n1 && j < n2) { 
    
        if (L[i] <= R[j]) { 
    
            arr[k] = L[i]; 
    
            i++; 
    
        } 
    
        else { 
    
            arr[k] = R[j]; 
    
            j++; 
        } 
    
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) { 
    
        arr[k] = L[i]; 
    
        i++; 
    
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
    
        arr[k] = R[j]; 
    
        j++; 
    
        k++; 
    } 
} 
  
void mergesort(int *arr, int l, int r) 
{ 
    if (l < r) { 
       
        int m = l+(r-l)/2; 
  
        // Sort two halves 
        mergesort(arr, l, m); 
        mergesort(arr, m+1, r); 
        // Merge two halves
        merge(arr, l, m, r); 
    } 
} 

void printArray(int *arr, int size) 
{  

    for (int i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    
    printf("\n"); 
}

/* Start_Rountine used in pthread_create */
void *sortArray(void *params)

{

    parameters* p = (parameters *)params;

    // SORT

    int begin = p->from_index;

    int end = p->to_index;

    int *array = p->arr;

    mergesort(array, begin, end);
    
    // Exit thread
    pthread_exit(0);
}

/* Start_Rountine used in pthread_create */
void *mergeArray(void *params) {
    
    parameters* p = (parameters *)params;

    // MERGE

    int begin = p->from_index;

    int end = p->to_index;

    int middle = begin +(end-begin)/2;

    int* array = p->arr;

    merge(array, begin, middle, end);

    // Exit thread
    pthread_exit(0);

}

void Multithread_MergeSort(int *arr, int length) {
    
    // Create 3 threads
    pthread_t threads[THREAD_COUNT];

    // Establish the first sorting thread

    parameters *data_1st = malloc (sizeof(parameters*));

    data_1st->from_index = 0;

    data_1st->to_index = 0 + ((length-1)/2);
    printf("middle: %d\n", data_1st->to_index);

    data_1st->arr = arr;

    pthread_create(&threads[0], 0, sortArray, data_1st);
    
    // Establish the second sorting thread

    parameters *data_2nd = malloc (sizeof(parameters*));

    data_2nd->from_index = ((length-1)/2) + 1;

    data_2nd->to_index = length - 1;

    data_2nd->arr = arr;

    pthread_create(&threads[1], 0, sortArray, data_2nd);

    // Wait for the 2 sorting threads to finish

    for (int i = 0; i < THREAD_COUNT - 1; i++)

        pthread_join(threads[i], NULL);

    // Establish the merge thread 

    parameters *data_3rd = malloc(sizeof(parameters*));

    data_3rd->from_index = 0;

    data_3rd->to_index = length - 1;

    data_3rd->arr = arr;

    pthread_create(&threads[2], 0, mergeArray, data_3rd);

    // Wait for the merge thread to finish 

    pthread_join(threads[2], NULL);

}