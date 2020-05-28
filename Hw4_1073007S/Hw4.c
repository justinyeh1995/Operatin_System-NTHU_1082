#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define THREAD_COUNT 5

void pickup_forks(int i);
void return_forks(int i);
void test(int i);
void init();
void *philosopher(void *param);

typedef struct {
    int index;
} parameters;

enum { thinking, hungry, eating } state[5];	// philospher's states
pthread_mutex_t lock;						// mutex to protect condition variables
pthread_cond_t self[5];                     // 5 condition variables

int main() {

    // Initialize philosophers' state & condition variable & mutex lock
    init();

    // Declare threads
    pthread_t threads[THREAD_COUNT];

    
    // Create threads in order
    for(int i = 0; i < THREAD_COUNT; i++) {

        parameters *param = malloc (sizeof(parameters*));
        
        param->index = i;

        pthread_create(&threads[i], 0, philosopher, param);
    }

    // Join threads in order
    for (int i = 0; i < THREAD_COUNT; i++) {

        pthread_join(threads[i], NULL);
    }

    return 0;
}

void init() {
    // Init seed
    srand((unsigned)time(0));
    
    // Init mutex lock
    pthread_mutex_init(&lock, NULL);
	
    // Init states to thinking and each condition variable
	for (int i = 0; i < THREAD_COUNT; i++ )	
	{
		state[i] = thinking;

		pthread_cond_init (&self[i], NULL);
    }
}

void pickup_forks(int i) {

    state[i] = hungry;

    test(i);

    /* Fail to pick up forks */
    pthread_mutex_lock(&lock);
    
    while(state[i] != eating) {

        printf("Philosopher %d can’t pick up forks and start waiting.\n", i);

        pthread_cond_wait(&self[i], &lock);

    }

    pthread_mutex_unlock(&lock);
    
}

void return_forks(int i) {

    state[i] = thinking;

    test((i+4)%5);

    test((i+1)%5);
}

void test(int i) {

    pthread_mutex_lock(&lock);

    if( (state[(i+4)%5] != eating) && 
        (state[i] == hungry) &&
        (state[(i+1)%5] != eating) ) {
            
            state[i] = eating;

            pthread_cond_signal(&self[i]);

    }

    pthread_mutex_unlock(&lock);
}

void *philosopher(void *param) {
    
    parameters *p = (parameters *)param;

    int index = p->index;

    int random = (int)(rand()%3 + 1);

    printf("Philosopher %d is now THINKING for %d seconds.\n", index, random);

    sleep(random);

    printf("Philosopher %d is now HUNGRY and trying to pick up forks.\n", index);

    pickup_forks(index);

    random = (int)(rand()%3 + 1);

    printf("Philosopher %d is now EATING.\n", index);

    sleep(random);

    printf("Philosopher %d returns forks and then starts TESTING %d and %d.\n", index, (index+4)%5, (index+1)%5);
    
    return_forks(index);

    //return NULL;

    pthread_exit(0);
}

