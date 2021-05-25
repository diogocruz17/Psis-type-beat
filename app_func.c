#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "KVS-lib.h"
#define KVS_LS_SOCK_PATH "/tmp/kvs_ls"

int init()
{
    struct sockaddr_un addr;
    int local_server;
    ssize_t numRead;
    
    local_server = socket(AF_UNIX, SOCK_STREAM, 0); /* Create client socket */
    if (local_server == -1){
        printf("Error creating socket\n");
        exit(-1);
    }
    /* Construct server address, and make the connection */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, KVS_LS_SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (connect(local_server, (struct sockaddr *) &addr,sizeof(struct sockaddr_un)) == -1){
        printf("Error connecting socket\n");
        exit(-1);
    }

    return local_server;
}