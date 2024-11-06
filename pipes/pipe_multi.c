#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
struct args
{
    int me;
    int *pipes;
};

int thread_pipes[5][2];
void* pipe_handler(void* arg){
    int*pipes= (int*)arg;
    char buf[16];
    while (1)
    {
        memset(buf,0,16);
        read(pipes[0],buf,16);
        for (size_t i = 0; i < 5; i++)
        {
            write(thread_pipes[i][1],buf,16);
        }
        
    }
    
}
void* thread_func(void* arg){
    int me=((struct args*)arg)->me;
    pipe(thread_pipes[me]);
    printf("%d waiting...\n",*(int*)arg);
    char  buf[16];
    memset(buf,0,16);
    read(thread_pipes[me][0],buf,16);
    printf("%d: %s\n",me,buf);
    printf("waiting done: %d\n",me);
}
int main(){
    pthread_t arr[5];
    struct args stuff[5];
    pthread_t threads[5];
    int pipes[2];
    pipe(pipes);
    for (size_t i = 0; i < 5; i++)
    {
        stuff[i].me=i;
        stuff[i].pipes=pipes;

    }
    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&threads[i],NULL,thread_func,&stuff[i]);
    }
    pthread_t th;
    pthread_create(&th,NULL,pipe_handler,pipes);
    sleep(5);
    write(pipes[1],"hi!",4);
    for (size_t i = 0; i < 5; i++)
    {
        pthread_join(threads[i],NULL);
    }
    
}