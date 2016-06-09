#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
	int pid;
	pid = fork();
	if(pid == 0)
	{
		for(int i=0; i < 5; i++)
		{
			printf("I'm children\n");
			sleep(1);
		}
	}
	else
	{
		wait(0);
		printf("I'm parent\n");
	} 
	return(0);
}
