#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
#define n_t 6
struct train
{
    int no;
    int seats;

};

void find_av(struct train* tr,char *buf,int n){
    int wr=0,i=0;

    while (wr<n && i<n_t)
    {
        wr+=sprintf(buf+wr,"%d %d\n",tr[i].no,tr[i].seats);

    }
    buf[wr]='\0';
    
}
int bookit(struct train* tr,int tr_no){
    if ( tr[tr_no].seats>0)
    {
        tr[tr_no].seats--;
        return 0;
    }
    return 1;
   
}
int main(){
    struct train trains[n_t];
    for (size_t i = 0; i < n_t; i++)
    {
        trains[i].no=i;
        trains[i].seats=6;
    }
    mkfifo("pippp",0666);
    FILE* f=fopen("pippp","rw");
    char buf[100],cmd[10];


    while (1)
    {
        fread(buf,1,10,f);
        int t_no;
        switch (cmd[0])
        {
        case '0':
            memset(buf,0,100);
            find_av(trains,buf,100);
            fwrite(buf,1,strlen(buf),f);
            break;
        case '1':
            sscanf(cmd,"%*d %d",&t_no);
            if (0==bookit(trains,t_no))
            {
                fwrite("ok",1,3,f);
            }else
            {
                fwrite("not ok",1,7,f);
            }
            break;
        default:
            break;
        }
    }
    

    
}