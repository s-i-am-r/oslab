#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    int mypipe[2];
    if (0 > pipe(mypipe))
    {
        return 1;
    }
    int x = fork();
    if (x == 0)
    {
        // child;
        char buf[16];
        memset(buf, 0, 16);

        int n = 1;
        for (size_t i = 1; i < 5; i++)
        {
            n *= i;
            sleep(1);
        }
        printf("cal done!\n");
        sprintf(buf, "sig: %d", n);
        write(mypipe[1], buf, 16);
    }
    else
    {
        // parent;
        char buf[16];
        memset(buf, 0, 16);

        for (size_t i = 0; i < 7; i++)
        {
            printf("parent: %d\n", i);
            
        }
        read(mypipe[0], buf, 16);
        printf("signal received: '%s'\n", buf);
    }
}