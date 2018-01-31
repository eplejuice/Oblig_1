#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 


void process(int number, int time) {
	printf("Prosess %d kjører\n", number);
	sleep(time);
	printf("Prosess %d kjørte i %d sekunder\n", number, time);
}

void forkcheck(int j){	// Sjekker at programmet forket riktig.
	if(j == 1){
	printf("Fork failed, exiting program");
	exit(EXIT_FAILURE);}	//Avslutter programmet hvis fork ikke ble riktig.
} 

int main(void){
	pid_t p = -1;
	pid_t p0 = -1;
	pid_t p1 = -1;
	pid_t p2 = -1;
	pid_t p3 = -1;
	pid_t p4 = -1;
	pid_t p5 = -1;

	//Henter prosessid-en til main.
	p = getpid();
	// Sjekker at man fortsatt er i main før man forker.
	if(p == getpid()){
	// Forker for å skape en parallell prosess.
	p0 = fork();
	forkcheck(p0);
	if(p == getpid()){
	p2 = fork();
	forkcheck(p2);
	}
	}
	// Sjekker at man er inne i den prosessen som kjører parallelt.
	if(!p0)
	{
	// Starter prosess funksjonen.
	process(0,1);
	}
	if(!p2)
	{
	process(2,3);
	}
	// Sjekker at man er tilbake i main før man så venter først på at p0 pro	
	// sessen skal gjøre seg ferdig for så å forke på nytt.
	if(p == getpid())
	{
	waitpid(p0,NULL,0);
	p1 = fork();
	forkcheck(p1);
	}
	// Lager prosessen p4.
	if(p == getpid())
	{
	p4 = fork();
	forkcheck(p4);
	}
	// Kjører funksjon i p1.
	if(!p1)
	{
	process(1,2);
	}
	// Kjører prosess i p4.
	if(!p4)
	{
	process(4,3);
	}
	// Venter på at p2 prosessen avsluttes før man forker p3.
	if(p == getpid())
	{
	waitpid(p2, NULL, 0);
	p3 = fork();
	forkcheck(p3);
	}
	// Kjører funksjon i p3 prossessen.
	if(!p3)
	{
	process(3,2);
	}
	// Venter på at p4 prosessen skal avsluttes før man lager p5 fork.
	if(p == getpid())
	{
	waitpid(p4,NULL,0);
	p5 = fork();
	forkcheck(p5);
	}
	// Kjører prosessen i p5.
	if(!p5)
	{
	process(5,3);
	}
	// Venter på at p5 prosessen skal fullføre seg før man avslutter main.
	if(p == getpid())
	{
	waitpid(p5,NULL,0);	
	}	
}

