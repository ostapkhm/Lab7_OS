#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


void* foo(void* arg){
    struct timeval start, end;

    gettimeofday(&start, NULL);
    long seconds;

    while(1){
        seconds = (end.tv_sec - start.tv_sec);
        usleep(100000);
        gettimeofday(&end, NULL);
        printf("Time of child thread passed %ld microseconds\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec);
    }

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    void *res;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, foo, NULL);

    time_t begin = time(NULL);

    sleep(2);
    pthread_cancel(tid);
    pthread_join(tid, &res);

    time_t end = time(NULL);
    printf("Time of parent thread passed %ld seconds\n", (end - begin));
}
