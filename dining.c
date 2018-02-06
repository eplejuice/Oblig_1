#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     /* usleep */
#include <pthread.h>
#include <semaphore.h>

#define SHARED		0
#define N		5
#define LEFT		(i+N-1)%N
#define RIGHT		(i+1)%N
#define	THINKING	0
#define HUNGRY		1
#define EATING		2
#define MAXSLEEP	5

int state[N];
sem_t mutex;
sem_t s[N];

void *philosophers(void *arg);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void think(int i);
void eat(int i);


int main()
{

	for(int i = 0; i < 5; i++)
	{
		sem_init(&s[i], SHARED, 0);
	}

	sem_init(&mutex, SHARED, 1);

	pthread_t ph[N];

	for(int i = 0 ; i< N; i++)
	{
		int *arg = malloc(sizeof(int));
		if ( arg == NULL ) {
			printf("Couldn't allocate memory for thread arg.\n");return -1;}
		*arg = i;
		pthread_create(&ph[i], NULL, philosophers, arg);
	}

	for(int i = 0; i< N; i++)
	{
		pthread_join(ph[i], NULL);
	}
}


void *philosophers(void *arg)
{
	int i = *(int*)arg;
	while(1){
		think(i);
		take_forks(i);
		eat(i);
		put_forks(i);
	}
}

void take_forks(int i)
{
	sem_wait(&mutex);
	state[i] = HUNGRY;
	test(i);
	sem_post(&mutex);
	sem_wait(&s[i]);
}

void put_forks(int i)
{
	sem_wait(&mutex);
	state[i] = THINKING;
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void test(int i)
{
	if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[i] = EATING;
		sem_post(&s[i]);
	}
}

void think(int i)
{
	printf("State of %d  is thinking\n", i);
	sleep(rand()%5);
}

void eat(int i)
{
	printf("State of %d is eating\n", i);
	sleep(rand()%5);
}	
