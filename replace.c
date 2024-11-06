#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        return 1;
    }
    char *s1 = argv[1];

    char *s2 = argv[2];
    size_t len_1 = strlen(s1);
    size_t len_2 = strlen(s2);
    int myfile = open("hi.txt", O_RDONLY);
    int lenn = 0;
    char buf[128];

    lenn = read(myfile, buf , 128);

    close(myfile);
    char *x;
    ssize_t off1 = 0;
    int newfile = open("new.txt", O_WRONLY | O_CREAT);
    do
    {
        x = strstr(buf + off1, s1);
        write(newfile, buf + off1, x - buf - off1);
        off1 = x - buf + len_1;
        write(newfile, s2, len_2);
    } while (!x);
    write(newfile, buf + off1, strlen(buf) - off1);
    close(newfile);
    return 0;
}