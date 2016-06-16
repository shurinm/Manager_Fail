#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main (void)

{
		int fd[2], strich, xxx;
		int pid;
		
		pipe(fd);
		pid = fork();
		if(pid == 0)
		{
			scanf("%d",&strich);
			write(fd[1], &strich, sizeof(int));
		}
		else
		{	
			read(fd[0], &strich, sizeof(int));
			printf("strich: %d/n", strich);
		}
		return(0);

};
