#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct array{
    int n;
    int * ptr;
    int size;
}int_array;

int_array* get_input(){
    FILE* myfile=fopen("input.txt","r");
   
    int * arr=malloc(n*sizeof(int));
    
    int_array* trex=malloc(sizeof(int_array));
    fscanf(myfile,"%d\n%d",&(trex->n),&(trex->size));
    trex->n=n;
    trex->size=0;
    trex->ptr=arr;
    
    for (int i=0;i<trex->size;i++)
    {
        fscanf(myfile,"%d",arr+i);
    }
    fclose(myfile);
    return trex;
    
}
typedef struct node
{
    int frame;
    int page;
    struct node* next;
}node;
typedef struct q{
    node* head;
    node*tail;

}q;

void page_them(q* fq,int_array* arr,int fr_sz){
    int done=0;
    int frames[fr_sz];
    for (size_t i = 0; i < fr_sz; i++)
    {
        frames[i]=-1;
    }

    
    for (; done< fr_sz;done++)
    {
        frames[done]=arr->ptr + done;    
    }
    while (done<arr->size)
    {
        
    }
    
    
}