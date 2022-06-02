#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct string_arr_struct {
    char **string_arr;
    unsigned int size;
    int start_idx;
};

void* show(void* arg){
    struct string_arr_struct *arg_struct = (struct string_arr_struct*) arg;

    int st_idx;
    int size = arg_struct->size;

    for(int i = 0; i < size; i++){
        st_idx = arg_struct->start_idx;
        if(i == size - 1){
            printf("%s\n", arg_struct->string_arr[(i + st_idx) % size]);
        }
        else printf("%s ", arg_struct->string_arr[(i + st_idx) % size]);
    }

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if(argc < 5){
        printf("Usage: %s <string1> <string2> <string3> <string4> [...<string-n>]\n", argv[0]);
        exit(-1);
    }

    unsigned int thread_amount = 4;
    pthread_t tids[thread_amount];

    int num_args = argc - 1;
    struct string_arr_struct args[thread_amount];

    for(int i = 0; i < thread_amount; i++){
        args[i].string_arr = argv + 1;
        args[i].size = num_args;
        args[i].start_idx = i;

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, show, &args[i]);
    }

    for(int i = 0; i < thread_amount; i++){
        pthread_join(tids[i], NULL);
    }

}
