#include<diren.h>
#include<stdio.h>
#include<sys/types.h>

void main()
{
	DIR *dp;
	int temp;
	char buf[15];
	printf("Dir Name: ");
	scanf("%s",buf);
	if((dp = opendir(buf)) == NULL)
	{
		temp=errno;
		printf("%d\n",temp);
		perror("opendir call");
		exit(1);
	}
	return;
}