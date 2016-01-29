//Prob4

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


void process_tree(int n)
{
	int i;				//iterator
	pid_t pid[2];		//Saving the pids of the process's 2 children
	int index[n];		//Saving the index
	index[0] = 1;		//Saving the process number
	printf("I'm the p1; my pid is %d;\n My ppid is %d\n\n",getpid(),getppid());
	for(i=1;i<n;i++)
	{
		pid[0] = fork();	
		if(!pid[0])		//the even child of the process
		{
			index[i] = index[i-1]*2; 
			printf("I'm the p%d; my pid is %d;\n My ppid is %d\n\n",index[i],getpid(),getppid());
		}
		else			//parent process
		{
			
			pid[1] = fork();
			if(!pid[1])		//the odd child of the process
			{
				index[i] = index[i-1]*2+1;
				printf("I'm the p%d; my pid is %d;\n My ppid is %d\n\n",index[i],getpid(),getppid());
			}
			else			//that's only for parent process
			{
				wait(NULL);  
				wait(NULL);   //waiting for its 2 children's death
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
		return 0;				
	}
	int i=0,n=0;
	for(i;argv[1][i];i++)
		n = 10*n+(argv[1][i]-'0'); //atoi
	if(n)	process_tree(n);
	return 1;
}

	