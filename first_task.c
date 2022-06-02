#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* show(void* arg){
    char *string = (char*) arg;

    for(int i = 0; i < 10; i++){
        printf("%s\n", string);
    }

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    char *string1 = "Child thread";
    char *string2 = "Parent thread";

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, show, string1);

    show((void **) string2);
}
