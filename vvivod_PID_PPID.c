#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<wait.h>

int main()
{
	pid_t pid; 
	pid = fork();
	if(pid == 0)
{
	printf("\nPID=%d PPID=%d\n", getpid(), getppid());

}
	else
{
	printf("PPID%d\n", getppid());
}
	return(0);
}
