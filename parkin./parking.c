#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<inttypes.h>
#include<signal.h>
pthread_t par_lot[29];
typedef struct queue{
    uint64_t index;
    struct queue* next;
}queue;
typedef struct q_head{
    int size;
    queue*head;
    queue*tail;
}q_head;
q_head cars,lots;
void push_queue(uint64_t n,q_head* myqueue){
    queue*tmp=malloc(sizeof(queue));
    tmp->index=n;
    tmp->next=NULL;
    if (!myqueue->size)
    {
        myqueue->head=myqueue->tail=tmp;
        myqueue->size=1;

        return;
    }
    myqueue->size++;
    myqueue->tail->next=tmp;
    myqueue->tail=tmp;
    
}
uint64_t pop_queue(q_head *myqueue){
    if (!myqueue->size)
    {
        perror("poping empty queue.");
        exit(EXIT_FAILURE);
    }
    uint64_t n= myqueue->head->index;
    queue*tmp=myqueue->head;
    myqueue->head=myqueue->head->next;
    free(tmp);
    myqueue->size--;
    return n;
}

void*park_a_car(void*arg){
    while (!lots.size)
    {
        printf("No spot:%lu\n",pthread_self());
        push_queue(pthread_self(),&cars);
        pause();
    }
    uint64_t n = pop_queue(&lots);
    par_lot[n]=pthread_self();
    printf("parked: car %lu in %d\n",par_lot[n],n);
    usleep(rand()%3000000);
    printf("released: car %lu in %d\n",par_lot[n],n);
    push_queue(n,&lots);
    if (cars.size)
    {
        pthread_t next_t=pop_queue(&cars);
        pthread_kill(next_t,SIGUSR1);
    }
    
    
}

int main(){
    for (size_t i = 0; i < 29; i++)
    {
        push_queue(i,&lots);
    }
    cars.size=0;
    pthread_t x;
    for (;;)
    {
        usleep(rand()%3000000);
        pthread_create(&x,NULL,park_a_car,NULL);
        pthread_detach(x);
    }
    
}
