#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void stop(void *tid){
    pthread_t id = *((pthread_t*) tid);
    printf("Quiting the child thread(TID -> %ld)!\n", id);
}

void* foo(void *arg){
    pthread_cleanup_push(stop, arg);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    long seconds;

    while(1){
        pthread_testcancel();

        seconds = (end.tv_sec - start.tv_sec);
        usleep(10000);
        gettimeofday(&end, NULL);
        printf("Time of child thread passed %ld microseconds\n", (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec);
    }

    pthread_cleanup_pop(0);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    void *res;
    pthread_t tid;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, foo, &tid);

    time_t begin = time(NULL);

    sleep(2);
    pthread_cancel(tid);

    pthread_join(tid, &res);

    time_t end = time(NULL);
    printf("Time of parent thread passed %ld seconds\n", (end - begin));
}
