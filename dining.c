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

int state[N]; // array med oversikt over status på filosofene.
sem_t mutex; 
sem_t s[N]; // array med semaphorer for filosofene.

void *philosophers(void *arg);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void think(int i);
void eat(int i);


int main()
{

	for(int i = 0; i < 5; i++) // setter semaphorene til å være null 
				   //slik at alle starter som thinking
	{
		sem_init(&s[i], SHARED, 0);
	}

	sem_init(&mutex, SHARED, 1); // setter mutex til å være hungry.

	pthread_t ph[N]; // array med oversikt over filosofer.

	for(int i = 0 ; i< N; i++) // løkke for å lage alle filosofene.
	{
		int *arg = malloc(sizeof(int)); // setter av plass til arg i minnet.
		if ( arg == NULL ) {
			printf("Couldn't allocate memory for thread arg.\n");return -1;}
		*arg = i; // setter arg til å peke på i.
		pthread_create(&ph[i], NULL, philosophers, arg); // lager filosofene som tråder.
	}

	for(int i = 0; i< N; i++) // venter på at alle trådene er ferdige.
	{
		pthread_join(ph[i], NULL);
	}
}


void *philosophers(void *arg)
{
	int i = *(int*)arg; // caster om arg til en int for å kunne sende den videre.
	while(1){  // filosofene går gjennom alle stadiene evig.
		think(i);
		take_forks(i);
		eat(i);
		put_forks(i);
	}
}

void take_forks(int i) 
// setter status til hungry, sjekker om gafler er tigjengelige og begynner å spise.
{
	sem_wait(&mutex);
	// teller ned semaforen, hvis den er 0 så blir tråden satt på vent.
	state[i] = HUNGRY;
	test(i);
	sem_post(&mutex);
	// vekker opp en tilfeldig tråd hvis semaforen går fra 0 til 1.
	sem_wait(&s[i]);
}

void put_forks(int i)
// setter status til thinking og ber de som sitter ved siden av sjekke om de kan begynne å spise.
{
	sem_wait(&mutex);
	state[i] = THINKING;
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void test(int i)
// hvis en filosof er sulten og gafler er tigjengelige, så begynner han å spise.
{
	if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[i] = EATING;
		sem_post(&s[i]);
	}
}

void think(int i)
// tenker et tilfeldig antall sekunder.
{
	printf("State of %d  is thinking\n", i);
	sleep(rand()%MAXSLEEP);
}

void eat(int i)
//spiser i et tilfeldig antall sekunder.
{
	printf("State of %d is eating\n", i);
	sleep(rand()%MAXSLEEP);
}	
