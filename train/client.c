#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int  main(){
    int writefd=open("pipo",O_WRONLY);
    int readfd=open("pipo",O_RDONLY);
    char buf[10],content[50];
    while (1)
    {
        printf("$ ");
        memset(buf,0,strlen(buf));
        fgets(buf,10,stdin);
        puts("scanned");
        write(writefd,buf,strlen(buf));
        usleep(1000);
        memset(content,0,50);
        read(readfd,content,50);
        printf("%s\n",content);

    }
    
  

}