
#define MAXLEN  256
#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>

typedef struct dirent *Dirp;

typedef struct queuenode
{
	char name[MAXLEN];
	struct queuenode* p;
}*Qpointer, Qnode;

void enqueue(Qpointer head, char* name)
{
	int i;
	Qpointer new = (Qpointer)malloc(sizeof(Qnode));
	for (i=0;name[i];i++ )
		new->name[i] = name[i];
	new->name[i] = name[i];
	head->p->p =new;
	head->p = new;
	new->p = head;
}

void pop(Qpointer tail,char *name)
{
	int i;
	Qpointer p=tail->p;
	for (i=0; p->name[i];i++ )
		name[i] = p->name[i];
	name[i] = p->name[i]; 
	tail->p = p->p;
	free(p);
}

int isqempty(Qpointer head, Qpointer tail)
{
	if (tail->p  == head)
	{
		free(head);
		free(tail);
		return 1;
	}
	else return 0;
}

int strcomp(char *a, char *b)
{
	int i;
	for(i=0;a[i]||b[i];i++)
		if(a[i]!=b[i]) return 0;
	return 1;
}

void traverse(char* dname, char* filename)
{
	Qpointer head,tail;
	head = (Qpointer)malloc(sizeof(Qnode));
	tail = (Qpointer)malloc(sizeof(Qnode));
	head->p = tail;
	tail->p = head;
	DIR *dp;
	Dirp d;
	char tempdir[MAXLEN],dir[MAXLEN];
	int i=0,j;
	if((dp = opendir(dname)) == NULL)
	{
		perror("opendir call");
		exit(1);
	}
	printf("/\n");
	dir[0] = '\0';
	tempdir[0] = '\0';


	chdir(dname);	
	
	while(1)
	{
		if (tempdir[0])
				tempdir[i++] = '/';
		while(d = readdir(dp))
		{

			if( d->d_ino && (d->d_name[0] !='.'))
			{
				if (dir[0]) 		printf("/%s",dir);

				printf("/%s",d->d_name);

				if (strcomp(filename,d->d_name))
				{
					printf(" is found!\n");
					return;
				}
				printf("\n");
				
				for(j=0;d->d_name[j];j++)
					tempdir[j+i] = d->d_name[j];
				tempdir[j+i] = '\0';
				enqueue(head,tempdir);
			}
		}
		closedir(dp);
		
		if(isqempty(head,tail)) 
		{
			printf("%s cannot be found\n",filename);
			return;
		}
		pop(tail,tempdir);
		while((dp = opendir(tempdir)) == NULL)
		{
			if (errno!=20)
			{
				printf("%s\n",tempdir);
				perror("error");
				exit(1);
			}	
			if(isqempty(head,tail)) 
			{
				printf("%s cannot be found\n",filename);
				return;
			}
			pop(tail,tempdir);	
					
		}
		for(i=0;tempdir[i];i++)
	 		dir[i] = tempdir[i];
		dir[i] = '\0';
	}
}

int main(int argc, char** argv)
{
	if (argc !=3)
	{
		printf("Usage: %s dir_name file_name\n", argv[0]);
		return 0;
	}
	traverse(argv[1],argv[2]);
	return 1;
}
	
