#include<stdio.h>
#include<stdlib.h>



int main(){
    FILE* f=fopen("pippp","wr");
    int cmd,t_no;
    char buf[100];
    while (1)
    {
        memset(buf,0,100);
        scanf("%d",&cmd);
        if (cmd==0)
        {
            fwrite("0",1,2,f);
            fread(buf,1,100,f);
        }else if (cmd==1)
        {

            scanf("%d",&t_no);
        }
        
        
    }
    
}