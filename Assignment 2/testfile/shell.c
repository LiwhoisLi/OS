#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char **argv)
{
  pid_t pid;
  if( pid = fork())
      wait(NULL);
  else  
    execl("test","test",NULL);
}
