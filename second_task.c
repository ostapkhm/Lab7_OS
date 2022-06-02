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
    if(argc < 2){
        printf("Usage: %s <string>\n", argv[0]);
        exit(-1);
    }

    char *string = argv[1];

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, show, string);

    //wait until child thread is done
    pthread_join(tid, NULL);
    printf("Child thread is done!\n");
    show((void **) string);
}
