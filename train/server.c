#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define TRAIN_COUNT 5
int train_seat_count[] = {
    12, 11, 3, 6, 9};
char *train_names[] = {
    "are", "mos", "blu", "kia", "sol"};
char train_details[50];
void update_details()
{
    memset(train_details, 0, 50);
    int written = 0;
    for (size_t i = 0; i < TRAIN_COUNT; i++)
    {
        written += sprintf(train_details + written, "%s: %d\n", train_names[i], train_seat_count[i]);
    }
    train_details[written] = '\0';
}
int main()
{
    mkfifo("pipo", 0644);
    int readfd = open("pipo", O_RDONLY);
    int writefd = open("pipo", O_WRONLY);
    char buf[10];
    int cmd = 99, tr_no = -1;
    while (1)
    {
        memset(buf, 0, 10);
        read(readfd, buf, 10);
        printf("from client: %s\n", buf);
        sscanf(buf, "%d", &cmd);
        if (cmd == 0)
        {
            update_details();
            write(writefd, train_details, strlen(train_details));
        }
        else if (cmd == 1)
        {
            if (2 > sscanf(buf, "%d %d", &cmd, &tr_no))
            {
                write(writefd, "inv!", 4);
            }
            else
            {

                memset(buf, 0, 10);
                if (train_seat_count[tr_no] > 0)
                {
                    train_seat_count[tr_no]--;
                    write(writefd, "done", 4);
                }
                else
                {
                    write(writefd, "not enough seats", 16);
                }
            }
        }
        else
        {
            write(writefd, "inv!", 4);
        }

        usleep(100000);
    }
}