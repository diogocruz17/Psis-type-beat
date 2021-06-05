#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "KVS-lib.h"
#define KVS_LS_SOCK_PATH "/tmp/kvs_ls"

int init()
{
    sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);


    struct sockaddr_un addr;
    int local_server;
    ssize_t numRead;

    local_server = socket(AF_UNIX, SOCK_STREAM, 0); /* Create client socket */
    if (local_server == -1)
    {
        printf("Error creating socket\n");
        exit(-1);
    }
    /* Construct server address, and make the connection */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, KVS_LS_SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (connect(local_server, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    {
        printf("Error connecting socket\n");
        exit(-1);
    }

    return local_server;
}

int check_status_connection(int status, char *group_id)
{
    if (status == -1)
    {
        printf("Lost connection to local server.Exiting...\n");
        return -1;
    }
    if (status == -2)
    {
        printf("Group doesn't exist.Try again\n");
        return 0;
    }
    if (status == -3)
    {
        printf("Secret is wrong.Try again\n");
        return 0;
    }
    if (status == -4)
    {
        printf("Couldnt reach authentication server.Try again\n");
        return 0;
    }
    if (status == 0)
    {
        printf("Connected to group:%s\n", group_id);
        return 1;
    }
}

int check_status_put(int status, char *key)
{
    if (status == -1)
    {
        printf("Lost connection to local server.Exiting...\n");
        return -1;
    }
    if (status == -2)
    {
        printf("Memory error in local server.No data was altered\n");
        return -2;
    }

    if (status == -5)
    {
        printf("The group was deleted.Exiting...\n");
        return -5;
    }
    if (status == 1)
    {
        printf("Value of key:%s edited\n", key);
        return 1;
    }
}

int check_status_get(int status,char* key,char* value)
{
    if (status == -1)
    {
        printf("Lost connection to local server.Exiting...\n");
        return -1;
    }
    if (status == -2)
    {
        printf("The key %s doesnt exist.Try again\n",key);
        return -2;
    }
    if (status == -5)
    {
        printf("The group was deleted.Exiting...\n");
        return -5;
    }
    if (status == 1)
    {
        printf("Key:%s\tValue:%s\n", key,value);
        free(value);
        return 1;
    }
}

int check_status_delete(int status,char* key)
{
    if (status == -1)
    {
        printf("Lost connection to local server.Exiting...\n");
        return -1;
    }
    if (status == -2)
    {
        printf("The key %s doesnt exist.Try again\n",key);
        return -2;
    }
    if (status == -5)
    {
        printf("The group was deleted.Exiting...\n");
        return -5;
    }
    if (status == 1)
    {
        printf("Value of key:%s was deleted\n", key);
        return 1;
    }

}