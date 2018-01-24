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

int main(void){
	pid_t p = -1;
	pid_t p0 = -1;
	pid_t p1 = -1;
	pid_t p2 = -1;
	pid_t p3 = -1;
	pid_t p4 = -1;
	pid_t p5 = -1;

	p = getpid();
	if(p == getpid()){
	p0 = fork();
		if(p == getpid()){
		p2 = fork();
		}
	}
	

	if(!p0)
	{
	process(0,1);
	}
	if(!p2)
	{
	process(2,3);
	}
	if(p == getpid())
	{
	waitpid(p0,NULL,0);
	p1 = fork();
	}
	if(p == getpid())
	{
	p4 = fork();
	}
	if(!p1)
	{
	process(1,2);
	}
	if(!p4)
	{
	process(4,3);
	}
	if(p == getpid())
	{
	waitpid(p2, NULL, 0);
	p3 = fork();
	}
	if(!p3)
	{
	process(3,2);
	}
	if(p == getpid())
	{
	waitpid(p4,NULL,0);
	p5 = fork();
	}
	if(!p5)
	{
	process(5,3);
	}
	if(p == getpid())
	{
	waitpid(p5,NULL,0);	
	}	
}

