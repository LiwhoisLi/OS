#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void do_child(void) {
    int i;
    while(1)
        i++;
}

int main(int argc, char **argv) {
    int count, delay, i;
    count = atoi(argv[1]);
    delay = atoi(argv[2]);

    for(i=0; i<count; i++) {
        printf("forking child %d of %d\n", i+1, count);
        if(fork() <= 0)
            do_child();
        sleep(delay);
    }
    wait(NULL);
}
