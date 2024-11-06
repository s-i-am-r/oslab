#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include <signal.h>

#define THINKING 0 
#define HUNGRY 1
#define EATING 2

int PHILS[5];
bool FORKS[5];
pthread_t THREADS[5];
void signal_handler(int signum) {
    printf("Thread received signal %d and woke up!\n", signum);
}
void a_phil(int me,bool* forks,int*phils,pthread_t * threads){
    think:
    phils[me]=THINKING;
    printf("%d: thinking...\n",me);
    usleep(5000000+rand()%5000000);
    try_eat:
    if (forks[me]&&forks[(me+1)%5])
    {

        forks[me]=forks[(me+1)%5]=false;
        phils[me]=EATING;
        printf("%d: eating...\n",me);

        usleep(5000000+rand()%5000000);
        forks[me]=forks[(me+1)%5]=true;
        if (phils[(me+4)%5]==HUNGRY&& forks[(me+4)%5])
        {
            pthread_kill(threads[(me+4)%5],SIGUSR1);
        }else if (phils[(me+1)%5]==HUNGRY&& forks[(me+2)%5])
        {
            pthread_kill(threads[(me+1)%5],SIGUSR1);

        }
        
        goto think;
    }else{
        phils[me]=HUNGRY;
        printf("%d: hungry...\n",me);
        pause();
        //forks[me]=forks[(me+1)%5]=false;
        goto try_eat;
    }
    
}

void*thread_func(void* n){
    int me=*(int*)n;
    signal(SIGUSR1, signal_handler);
    a_phil(me,FORKS,PHILS,THREADS);
}

int main(){
    int tmp[]={0,1,2,3,4};
    for (size_t i = 0; i < 5; i++)
    {
        FORKS[i]=true;
    }
    
    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&THREADS[i], NULL, thread_func, &tmp[i]);
    }
    for (size_t i = 0; i < 5; i++)
    {
        pthread_join(THREADS[i],NULL);
    }
    
}