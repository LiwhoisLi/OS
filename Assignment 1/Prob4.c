#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


void process_tree(int n)
{
	int i;
	pid_t pid[2];
	int index[n];
	index[0] = 1;
	printf("I'm the p1; my pid is %d;\n My ppid is %d\n",getpid(),getppid());
	for(i=1;i<n;i++)
	{
		pid[0] = fork();
		if(!pid[0])
		{
			index[i] = index[i-1]*2; 
			printf("I'm the p%d; my pid is %d;\n My ppid is %d\n",index[i],getpid(),getppid());
		}
		else
		{
			
			pid[1] = fork();
			if(!pid[1])
			{
				index[i] = index[i-1]*2+1;
				printf("I'm the p%d; my pid is %d;\n My ppid is %d\n",index[i],getpid(),getppid());
			}
			else	
			{
				wait(NULL);
				wait(NULL);
				break;
			}
		}
	
	}
}

int main(int argc,char **argv)
{
	if (argc!=2)
	{
		printf("Usage: %s <int>depth\n",argv[0]);
	}
	int i=0,n=0;
	for(i;argv[1][i];i++)
		n = 10*n+(argv[1][i]-'0');
	//printf("%d\n",n);
	if(n)	process_tree(n);
	return 1;
}

	