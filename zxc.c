#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
{
	printf("\nPID=%d\n", getpid());
}
	else
{
	printf("PPID=%d", getpid());
}
 
	return(0);
}
